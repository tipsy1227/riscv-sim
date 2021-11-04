#include <stdlib.h>

/* abort: abort current emulation */
__attribute__((noreturn)) void abort(){
	_Exit(EXIT_FAILURE);

	__builtin_unreachable();
}

