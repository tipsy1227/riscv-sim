.include "env/arch/constants.s"

.section .text.init,"ax",@progbits
.globl _start

#
# setup and jump to simlib_start
#

_start:
    # setup default trap vector
    la      t0, trap_vector
    csrw    mtvec, t0

    # set up stack pointer
    la      sp, _memory_end

    jal     _arch_setup
	j       simlib_start

#
# start of trap handler
#
    .align 2
trap_vector:
    # Save registers.
    addi    sp, sp, -CONTEXT_SIZE
    sw      ra, 0(sp)
    sw      a0, 4(sp)
    sw      a1, 8(sp)
    sw      a2, 12(sp)
    sw      a3, 16(sp)
    sw      a4, 20(sp)
    sw      a5, 24(sp)
    sw      a6, 28(sp)
    sw      a7, 32(sp)
    sw      t0, 36(sp)
    sw      t1, 40(sp)
    sw      t2, 44(sp)
    sw      t3, 48(sp)
    sw      t4, 52(sp)
    sw      t5, 56(sp)
    sw      t6, 60(sp)

    # Invoke the handler.
    mv      a0, sp
    csrr    a1, mcause
    csrr    a2, mepc
    jal     trap_handler

    # Restore registers.
    sw      ra, 0(sp)
    sw      a0, 4(sp)
    sw      a1, 8(sp)
    sw      a2, 12(sp)
    sw      a3, 16(sp)
    sw      a4, 20(sp)
    sw      a5, 24(sp)
    sw      a6, 28(sp)
    sw      a7, 32(sp)
    sw      t0, 36(sp)
    sw      t1, 40(sp)
    sw      t2, 44(sp)
    sw      t3, 48(sp)
    sw      t4, 52(sp)
    sw      t5, 56(sp)
    sw      t6, 60(sp)
    addi sp, sp, CONTEXT_SIZE

    # Return
    mret

    .bss

