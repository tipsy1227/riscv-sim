.section .text.init,"ax",@progbits
.globl _start

_start:
	# setup stack pointer
	la sp, _memory_end

	# setup trap handler
	la t0, trap_handler
	addi t0, t0, 1
	csrw mtvec, t0

	# setup finisher device
	jal finisher_init

	# setup UART device
	li a0, 399193 # baudrate default to 399193
	jal uart_init

	# transfer control to thread_start
	j cooperat_start

