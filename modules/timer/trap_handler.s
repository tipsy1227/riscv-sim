.globl trap_handler

.align 2
trap_handler:
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j mti_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler
	j default_handler

