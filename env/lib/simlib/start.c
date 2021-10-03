#include <stdlib.h>
#include <stddef.h>

extern int main(int argc, char **argv);

/* simlib_start: call the user-defined main function then stop the emulation when return */
__attribute__((noreturn)) void simlib_start(){
	char *argv[] = {"simlib", NULL};
	exit(main(1,argv));
	__builtin_unreachable();
}

