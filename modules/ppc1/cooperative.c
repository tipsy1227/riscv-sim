#include <arch/reg.h>
#include <stdlib.h>
#include <setjmp.h>

#include "cooperative.h"

extern int main();
extern char _memory_end[];

typedef void (*tfp_t)(void);         // type for thread function pointer

static int tid;                  // tid indicated the current running thread
static int tmap;                 // a bitmap indicate which thread is in use
static jmp_buf tenv[MAXTHREADS]; // buffer for saving the environments of threads
static tfp_t tfp[MAXTHREADS];    // to save function pointers of threads

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

/* cooperat_start: setup data for threads and ivoke the main function as a thread */
void cooperat_start(){
	// setup data and create a thread for main function
	tmap = 0;
	tid = thread_create(main);

	// start the main thread
	longjmp(tenv[tid], 0);

	__builtin_unreachable();
}

/* thread_create: create a new thread for the provided function */
int thread_create(void *fp){
	static jmp_buf env_crt; // buf used when create a new thread
	int nid;                // thread id for the new created thread

	if((nid = next_empty_thread()) == -1) // return -1 if all thread is in use
		return -1;

	tfp[nid] = fp;    // buffer the entry point for new created thread
	tmap |= 1 << nid; // indicate the new thread as non-empty

	if(!setjmp(env_crt)){ // save the current environment into env_crt
		// setup the environment for the new created thread
		reg_write(sp, (unsigned int)_memory_end - STACKSIZE * nid);

		if(!setjmp(tenv[nid])) // stop at entry of the new created thread
			longjmp(env_crt, 0); // restore the environment
		else
			thread_start();
	}

	// return the thread id of new created thread
	return nid;
}

/* thread_yield: yield control to another thread if any */
void thread_yield(){
	if(!setjmp(tenv[tid])){ // save the current environment into its thread buffer
		// restore to the picked thread
		tid = next_thread();
		longjmp(tenv[tid], 0);
	}
}

/* thread_exit: exit from the current running thread */
void thread_exit(){
	tmap &= ~(1 << tid);

	if(tmap){
		// restore to the picked thread
		tid = next_thread();
		longjmp(tenv[tid], 0);
	} else{ // stop emulation if there is no more thread to be execute
		exit(0);
	}

	__builtin_unreachable();
}

