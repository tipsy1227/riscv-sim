#pragma once

/* reg_read: read registers */
#define reg_read(reg) ({ \
	register int reg asm(#reg); \
	reg; \
})

/* reg_write: write CSRs and return the previous content */
#define reg_write(reg, cnt) ({ \
	register int reg asm(#reg); \
	register int tmp; \
	tmp = reg; \
	reg = cnt; \
	tmp; \
})

