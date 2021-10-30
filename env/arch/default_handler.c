#include <arch/csr.h>
#include <stdlib.h>

/* default_handler: exit with the mcause code */
__attribute__((interrupt)) void default_handler(){
	int mcause = csr_read(mcause);
	exit(((mcause & MCAUS_INTR) >> 16) | (mcause & MCAUS_CODE));
}

