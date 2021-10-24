.include "arch/const.s"

.globl setjmp

setjmp:
	sw ra,  0*REGSIZE(a0)
	sw s0,  1*REGSIZE(a0)
	sw s1,  2*REGSIZE(a0)
	sw s2,  3*REGSIZE(a0)
	sw s3,  4*REGSIZE(a0)
	sw s4,  5*REGSIZE(a0)
	sw s5,  6*REGSIZE(a0)
	sw s6,  7*REGSIZE(a0)
	sw s7,  8*REGSIZE(a0)
	sw s8,  9*REGSIZE(a0)
	sw s9,  10*REGSIZE(a0)
	sw s10, 11*REGSIZE(a0)
	sw s11, 12*REGSIZE(a0)
	sw sp,  13*REGSIZE(a0)

	li a0, 0
	ret

