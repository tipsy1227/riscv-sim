.section .text.init,"ax",@progbits
.globl _start

_start:
	# setup stack pointer
	la sp, _memory_end

	# setup trap handler
	la t0, trap_handler
	csrw mtvec, t0

	# setup finisher device
	jal finisher_init

	# setup UART device
	li a0, 399193 # baudrate default to 399193
	jal uart_init

	# transfer control to thread_start
	j thread_start

