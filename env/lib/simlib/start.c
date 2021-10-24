#include <stdlib.h>
#include <stddef.h>

extern int main(int argc, char **argv);

/* _simlib_start: call the user-defined main function then stop the emulation when return */
__attribute__((noreturn)) void _simlib_start(){
	char *argv[] = {"riscv-sim", NULL};
//	memset(_bss_start, 0, _bss_end - _bss_start);
	exit(main(1,argv));
	__builtin_unreachable();
}

