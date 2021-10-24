#include <stdlib.h>
#include <arch/finisher.h>

/* exit: exit from the simulation with status code */
__attribute__((noreturn)) void exit(int status){
	finisher_exit(status);
	__builtin_unreachable();
}

