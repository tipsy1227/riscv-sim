#include <arch/csr.h>

/* csr_read: read CSRs */
__attribute__((weak)) int csr_read(int csr){
	switch(csr){
	case mstatus:
		asm("csrr a5, mstatus");
		break;
	case mie:
		asm("csrr a5, mie");
		break;
	case mtvec:
		asm("csrr a5, mtvec");
		break;
	case mepc:
		asm("csrr a5, mepc");
		break;
	case mcause:
		asm("csrr a5, mcause");
		break;
	case mip:
		asm("csrr a5, mip");
		break;
	}
}

/* csr_write: write CSRs and return the original content */
__attribute__((weak)) int csr_write(int csr, int cnt){
	switch(csr){
	case mstatus:
		asm("csrrw a5, mstatus, a1");
		break;
	case mie:
		asm("csrrw a5, mie, a1");
		break;
	case mtvec:
		asm("csrrw a5, mtvec, a1");
		break;
	case mepc:
		asm("csrrw a5, mepc, a1");
		break;
	case mcause:
		asm("csrrw a5, mcause, a1");
		break;
	case mip:
		asm("csrrw a5, mip, a1");
		break;
	}
}

/* csr_set: set bits in CSRs and return the original content */
__attribute__((weak)) int csr_set(int csr, int mask){
	switch(csr){
	case mstatus:
		asm("csrrs a5, mstatus, a1");
		break;
	case mie:
		asm("csrrs a5, mie, a1");
		break;
	case mtvec:
		asm("csrrs a5, mtvec, a1");
		break;
	case mepc:
		asm("csrrs a5, mepc, a1");
		break;
	case mcause:
		asm("csrrs a5, mcause, a1");
		break;
	case mip:
		asm("csrrs a5, mip, a1");
		break;
	}
}

/* csr_clear: clear bits in CSRs and return the original content */
__attribute__((weak)) int csr_clear(int csr, int mask){
	switch(csr){
	case mstatus:
		asm("csrrc a5, mstatus, a1");
		break;
	case mie:
		asm("csrrc a5, mie, a1");
		break;
	case mtvec:
		asm("csrrc a5, mtvec, a1");
		break;
	case mepc:
		asm("csrrc a5, mepc, a1");
		break;
	case mcause:
		asm("csrrc a5, mcause, a1");
		break;
	case mip:
		asm("csrrc a5, mip, a1");
		break;
	}
}

