.section .text.init,"ax",@progbits
.globl _start

_start:
	# setup stack pointer
	la sp, _memory_end

	# setup uart device
	jal uart_setup

	# setup trap handler
	la t0, trap_handler
	addi t0, t0, 1
	csrw mtvec, t0

	# set mtimecmp register to be 0
	li a0, 0
	li a1, 0
	jal set_mtimecmp

	# enable machine timer interrupt
	li t0, 0x8
	csrw mstatus, t0
	li t0, 0x80
	csrw mie, t0

busy:
	j busy

