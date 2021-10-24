.equ REGSIZE,      4
.equ SAVE_REGS,   16
.equ CONTEXT_SIZE, (SAVE_REGS * REGSIZE)

.globl trap_handler

.align 2
trap_handler:
	addi    sp, sp, -CONTEXT_SIZE
	sw      ra, 0*REGSIZE(sp)
	sw      a0, 1*REGSIZE(sp)
	sw      a1, 2*REGSIZE(sp)
	sw      a2, 3*REGSIZE(sp)
	sw      a3, 4*REGSIZE(sp)
	sw      a4, 5*REGSIZE(sp)
	sw      a5, 6*REGSIZE(sp)
	sw      a6, 7*REGSIZE(sp)
	sw      a7, 8*REGSIZE(sp)
	sw      t0, 9*REGSIZE(sp)
	sw      t1, 10*REGSIZE(sp)
	sw      t2, 11*REGSIZE(sp)
	sw      t3, 12*REGSIZE(sp)
	sw      t4, 13*REGSIZE(sp)
	sw      t5, 14*REGSIZE(sp)
	sw      t6, 15*REGSIZE(sp)

	# Invoke the handler
	csrr    a0, mcause
	csrr    a1, mepc
	mv      a2, sp
	jal     _trap_handler

	# Restore registers.
	lw      ra, 0*REGSIZE(sp)
	lw      a0, 1*REGSIZE(sp)
	lw      a1, 2*REGSIZE(sp)
	lw      a2, 3*REGSIZE(sp)
	lw      a3, 4*REGSIZE(sp)
	lw      a4, 5*REGSIZE(sp)
	lw      a5, 6*REGSIZE(sp)
	lw      a6, 7*REGSIZE(sp)
	lw      a7, 8*REGSIZE(sp)
	lw      t0, 9*REGSIZE(sp)
	lw      t1, 10*REGSIZE(sp)
	lw      t2, 11*REGSIZE(sp)
	lw      t3, 12*REGSIZE(sp)
	lw      t4, 13*REGSIZE(sp)
	lw      t5, 14*REGSIZE(sp)
	lw      t6, 15*REGSIZE(sp)
	addi sp, sp, CONTEXT_SIZE

	# Return
	mret

