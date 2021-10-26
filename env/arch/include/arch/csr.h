#pragma once

#include <arch/const.h>

/* csr_read: read CSRs */
#define csr_read(csr) ({ \
	register int t0 asm("t0"); \
	asm("csrr t0, "#csr";"); \
	t0; \
})

/* csr_write: write CSRs and return the previous content */
#define csr_write(csr, cnt) ({ \
	__attribute__((unused)) register int t0 asm("t0") = cnt; \
	register int t1 asm("t1"); \
	asm( \
		"csrrw t1, "#csr", t0;" \
	); \
	t1; \
})

/* csr_set: set bits in CSRs and return the previous content */
#define csr_set(csr, cnt) ({ \
	__attribute__((unused)) register int t0 asm("t0") = cnt; \
	register int t1 asm("t1"); \
	asm( \
		"csrrs t1, "#csr", t0;" \
	); \
	t1; \
})

/* csr_clear: clear bits in CSRs and return the previous content */
#define csr_clear(csr, cnt) ({ \
	__attribute__((unused)) register int t0 asm("t0") = cnt; \
	register int t1 asm("t1"); \
	asm( \
		"csrrc t1, "#csr", t0;" \
	); \
	t1; \
})

/* constants for mstatus register */
enum{
	// masks
	MSTAT_UIE = 0x0001,
	MSTAT_SIE = 0x0002,
	MSTAT_MIE = 0x0008,
	MSTAT_UPIE = 0x0010,
	MSTAT_SPIE = 0x0020,
	MSTAT_MPIE = 0x0080,
	MSTAT_SPP = 0x01000,
	MSTAT_MPP = 0x1800,
};

/* constants for mie register */
enum{
	// masks
	MIE_USIE = 0x0001,
	MIE_SSIE = 0x0002,
	MIE_MSIE = 0x0008,
	MIE_UTIE = 0x0010,
	MIE_STIE = 0x0020,
	MIE_MTIE = 0x0080,
	MIE_UEIE = 0x0100,
	MIE_SEIE = 0x0200,
	MIE_MEIE = 0x0800,
};

/* constants for mip register */
enum{
	// masks
	MIE_USIP = 0x0001,
	MIE_SSIP = 0x0002,
	MIE_MSIP = 0x0008,
	MIE_UTIP = 0x0010,
	MIE_STIP = 0x0020,
	MIE_MTIP = 0x0080,
	MIE_UEIP = 0x0100,
	MIE_SEIP = 0x0200,
	MIE_MEIP = 0x0800,
};

/* constants for mcause register */
enum{
	// masks
	MCAUS_INTR = 1 << (MXLEN - 1),
	MCAUS_CODE = ~(1 << (MXLEN - 1)),

	MCAUS_USI = MCAUS_INTR | 0,
	MCAUS_SSI = MCAUS_INTR | 1,
	MCAUS_MSI = MCAUS_INTR | 3,
	MCAUS_UTI = MCAUS_INTR | 4,
	MCAUS_STI = MCAUS_INTR | 5,
	MCAUS_MTI = MCAUS_INTR | 7,
	MCAUS_UEI = MCAUS_INTR | 8,
	MCAUS_SEI = MCAUS_INTR | 9,
	MCAUS_MEI = MCAUS_INTR | 11,
};

