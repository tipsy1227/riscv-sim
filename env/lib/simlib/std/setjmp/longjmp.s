.include "arch/const.s"

.globl longjmp

longjmp:
	lw ra,  0*REGSIZE(a0)
	lw s0,  1*REGSIZE(a0)
	lw s1,  2*REGSIZE(a0)
	lw s2,  3*REGSIZE(a0)
	lw s3,  4*REGSIZE(a0)
	lw s4,  5*REGSIZE(a0)
	lw s5,  6*REGSIZE(a0)
	lw s6,  7*REGSIZE(a0)
	lw s7,  8*REGSIZE(a0)
	lw s8,  9*REGSIZE(a0)
	lw s9,  10*REGSIZE(a0)
	lw s10, 11*REGSIZE(a0)
	lw s11, 12*REGSIZE(a0)
	lw sp,  13*REGSIZE(a0)

	seqz a0, a1
	add a0, a0, a1 # a0 = (a1 == 0)? 1: a1
	ret

