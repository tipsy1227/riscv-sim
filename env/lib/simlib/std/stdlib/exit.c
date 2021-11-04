#include <stdlib.h>
#include <arch/csr.h>
#include <arch/finisher.h>

#define MAX_EXIT 32

typedef void (*Exit_fp_t)(void);

static Exit_fp_t efp[MAX_EXIT];
static int nefp = 0;

/* _Exit: exit from the simulation with status code without terminating processes */
__attribute__((noreturn)) void _Exit(int status){
	finisher_exit(status);

	__builtin_unreachable();
}

/* exit: exit from the simulation with status code */
__attribute__((noreturn)) void exit(int status){
	// execute functions registered with atexit
	for(int i = nefp - 1; i >= 0; --i)
		(*efp[i])();

	_Exit(status);

	__builtin_unreachable();
}

/* atexit: register a function to be executed at exit */
int atexit(Exit_fp_t fp){
	int tmp = csr_clear(mstatus, MSTAT_MIE); // enter critical section

	int r = -1;
	if(nefp < MAX_EXIT){
		r = 0;
		efp[nefp++] = fp;
	}

	csr_write(mstatus, tmp); // exit from critical section
	return r; // return 0 on success, -1 otherwise
}

