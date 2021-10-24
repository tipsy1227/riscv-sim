#include <arch/const.h>
#include <arch/trap.h>
#include <arch/csr.h>
#include <stdlib.h>

typedef void (*trap_hd)(int, int, int *);
static trap_hd handler[2][16] = {0}; // trap handlers

/* default_handler: exit with the mcause code */
static void default_handler(int mcause, int mepc, int *regs){
	exit(((mcause & MCAUS_INTR) >> 16) | (mcause & MCAUS_CODE));
}

/* _trap_handler: ivoke the corresponding handler according to the mcause register */
__attribute__((weak)) void _trap_handler(int mcause, int mepc, int *regs){
	int intr = (mcause < 0)? 1: 0;
	int code = mcause & MCAUS_CODE;

	if(handler[intr][code])
		(*handler[intr][code])(mcause, mepc, regs);
	else
		default_handler(mcause, mepc, regs);
}

/* get_trap_hd: get the trap handler for the mcause number */
__attribute__((weak)) void *get_trap_hd(int mcause){
	int intr = (mcause < 0)? 1: 0;
	int code = mcause & MCAUS_CODE;

	return handler[intr][code];
}

/* set_trap_hd: set the trap handler for the mcause number and return the previous handler */
__attribute__((weak)) void *set_trap_hd(int mcause, void *hd){
	void *phd;
	int intr = (mcause < 0)? 1: 0;
	int code = mcause & MCAUS_CODE;

	phd = handler[intr][code];
	handler[intr][code] = hd;
	return phd;
}

