#include <arch.h>
#include <stdlib.h>

/* exit: exit from the simulation with status code */
__attribute__((noreturn)) void exit(int status){
	_finisher_exit(status);
	__builtin_unreachable();
}

