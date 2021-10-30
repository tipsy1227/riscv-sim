#include <arch/const.h>
#include <arch/reg.h>
#include <arch/csr.h>
#include <arch/timer.h>
#include <stdlib.h>

#include "preemptive.h"

#define SAVEREGS 28
#define CONTEXTSIZE (REGSIZE * SAVEREGS)

extern int main();
extern char _memory_end[];

typedef void (*tfp_t)(void);     // type for thread function pointer

static int tid;                  // integer indicated the current running thread
static int tmap;                 // bitmap indicate which thread is in use
static int tpc[MAXTHREADS];      // program counters for threads
static int tsp[MAXTHREADS];      // stack pointers for threads
static tfp_t tfp[MAXTHREADS];    // function pointers for threads

static int timeslice = 100000;

#define STORE asm( \
	".include \"arch/const.s\";" \
	".equ SAVEREGS, 28;" \
	".equ CONTEXTSIZE, (REGSIZE * SAVEREGS);" \
	"addi sp, sp, -CONTEXTSIZE;" \
	"sw ra,   0*REGSIZE(sp);" \
	"sw t0,   1*REGSIZE(sp);" \
	"sw t1,   2*REGSIZE(sp);" \
	"sw t2,   3*REGSIZE(sp);" \
	"sw t3,   4*REGSIZE(sp);" \
	"sw t4,   5*REGSIZE(sp);" \
	"sw t5,   6*REGSIZE(sp);" \
	"sw t6,   7*REGSIZE(sp);" \
	"sw a0,   8*REGSIZE(sp);" \
	"sw a1,   9*REGSIZE(sp);" \
	"sw a2,  10*REGSIZE(sp);" \
	"sw a3,  11*REGSIZE(sp);" \
	"sw a4,  12*REGSIZE(sp);" \
	"sw a5,  13*REGSIZE(sp);" \
	"sw a6,  14*REGSIZE(sp);" \
	"sw a7,  15*REGSIZE(sp);" \
	"sw s0,  16*REGSIZE(sp);" \
	"sw s1,  17*REGSIZE(sp);" \
	"sw s2,  18*REGSIZE(sp);" \
	"sw s3,  19*REGSIZE(sp);" \
	"sw s4,  20*REGSIZE(sp);" \
	"sw s5,  21*REGSIZE(sp);" \
	"sw s6,  22*REGSIZE(sp);" \
	"sw s7,  23*REGSIZE(sp);" \
	"sw s8,  24*REGSIZE(sp);" \
	"sw s9,  25*REGSIZE(sp);" \
	"sw s10, 26*REGSIZE(sp);" \
	"sw s11, 27*REGSIZE(sp);" \
)

#define RESTORE asm( \
	".include \"arch/const.s\";" \
	".equ SAVEREGS, 28;" \
	".equ CONTEXTSIZE, (REGSIZE * SAVEREGS);" \
	"lw ra,   0*REGSIZE(sp);" \
	"lw t0,   1*REGSIZE(sp);" \
	"lw t1,   2*REGSIZE(sp);" \
	"lw t2,   3*REGSIZE(sp);" \
	"lw t3,   4*REGSIZE(sp);" \
	"lw t4,   5*REGSIZE(sp);" \
	"lw t5,   6*REGSIZE(sp);" \
	"lw t6,   7*REGSIZE(sp);" \
	"lw a0,   8*REGSIZE(sp);" \
	"lw a1,   9*REGSIZE(sp);" \
	"lw a2,  10*REGSIZE(sp);" \
	"lw a3,  11*REGSIZE(sp);" \
	"lw a4,  12*REGSIZE(sp);" \
	"lw a5,  13*REGSIZE(sp);" \
	"lw a6,  14*REGSIZE(sp);" \
	"lw a7,  15*REGSIZE(sp);" \
	"lw s0,  16*REGSIZE(sp);" \
	"lw s1,  17*REGSIZE(sp);" \
	"lw s2,  18*REGSIZE(sp);" \
	"lw s3,  19*REGSIZE(sp);" \
	"lw s4,  20*REGSIZE(sp);" \
	"lw s5,  21*REGSIZE(sp);" \
	"lw s6,  22*REGSIZE(sp);" \
	"lw s7,  23*REGSIZE(sp);" \
	"lw s8,  24*REGSIZE(sp);" \
	"lw s9,  25*REGSIZE(sp);" \
	"lw s10, 26*REGSIZE(sp);" \
	"lw s11, 27*REGSIZE(sp);" \
	"addi sp, sp, CONTEXTSIZE;" \
)

/* next_thread: return the next active thread */
static int next_thread(){
	// pick up the next active thread based on round-robin policy
	int nid = tid;
	do{
		nid = (nid + 1) % MAXTHREADS;
	} while(!((tmap >> nid) & 1));
	return nid;
}

/* next_empty_thread: return thread id of an empty thread, -1 if there is no one */
static int next_empty_thread(){
	int id = -1;
	for(int i = 0; i < MAXTHREADS; ++i){
		if(!((tmap >> i) & 1)){
			id = i;
			break;
		}
	}
	return id;
}

/* thread_start: invoke the thread function for current tid and exit after it */
static void thread_start(){
	(*tfp[tid])();
	thread_exit();

	__builtin_unreachable();
}

/* preempt_start: setup data for threads and ivoke the main function as a thread */
void preempt_start(){
	// setup data and create a thread for main function
	tmap = 0;

	// use the last thread to temporary store data for creating main thread
	tid = MAXTHREADS - 1;
	reg_write(sp, (unsigned int)_memory_end - STACKSIZE * tid - CONTEXTSIZE);

	thread_create(main);

	// enable maching timer interrupt and trigger it immediately
	set_mtimecmp(0);
	csr_set(mstatus, MSTAT_MIE);
	csr_set(mie, MIE_MTIE);

	__builtin_unreachable();
}

/* mti_handler: switch between threads every timer interrupt */
__attribute__((naked)) void mti_handler(){
	// store the program status of the current thread
	STORE;
	tsp[tid] = reg_read(sp);
	tpc[tid] = csr_read(mepc);

	set_mtimecmp(get_mtime() + timeslice); // next timer interrupt
	tid = next_thread(); // switch to the next thread

	// restore the program status of the next thread
	reg_write(sp, tsp[tid]);
	csr_write(mepc, tpc[tid]);
	RESTORE;

	asm("mret"); // return from the interrupt
}

/* thread_create: create a new thread for the provided function */
int thread_create(void *fp){
	int nid;                // thread id for the new created thread

	csr_clear(mstatus, MSTAT_MIE); // enter the critical section

	if((nid = next_empty_thread()) == -1) // return -1 if all thread is in use
		return -1;

	tfp[nid] = fp;                 // buffer the function for new created thread
	tmap |= 1 << nid; // indicate the new thread as non-empty

	// setup the program state for the new created thread
	tsp[nid] = (unsigned int)_memory_end - STACKSIZE * nid - CONTEXTSIZE; // buffer the new stack pointer
	tpc[nid] = (int)&thread_start; // buffer the entry point of new created thread
	
	csr_set(mstatus, MSTAT_MIE); // exit from the critical section

	// return the thread id of new created thread
	return nid;
}

/* thread_yield: yield control to another thread if any */
void thread_yield(){
	csr_clear(mstatus, MSTAT_MIE); // enter the critical section
	set_mtimecmp(0); // set mtimecmp to 0 to trigger the machine timer interrupt
	csr_set(mstatus, MSTAT_MIE); // exit from the critical section
}

/* thread_exit: exit from the current running thread */
void thread_exit(){
	csr_clear(mstatus, MSTAT_MIE); // enter the critical section
	tmap &= ~(1 << tid);
	if(tmap){
		set_mtimecmp(0); // set mtimecmp to 0 to trigger the machine timer interrupt
		csr_set(mstatus, MSTAT_MIE); // exit from the critical section
	} else { // stop emulation if there is no more thread to be execute
		exit(0);
	}

	__builtin_unreachable();
}

