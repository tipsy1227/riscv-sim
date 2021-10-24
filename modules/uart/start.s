.section .text.init,"ax",@progbits
.globl _start

_start:
	# setup stack pointer and jump to main
	la sp, _memory_end
	j main
