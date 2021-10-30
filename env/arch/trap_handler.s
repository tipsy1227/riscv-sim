.weak trap_handler

.align 2
trap_handler:
	j default_handler # exceptions
	j default_handler # supervisor software interrupt
	j default_handler
	j default_handler # machine software interrupt
	j default_handler # user timer interrupt
	j default_handler # supervisor timer interrupt
	j default_handler
	j default_handler # machine timer interrupt
	j default_handler # user external interrupt
	j default_handler # supervisor external interrupt
	j default_handler
	j default_handler # machine external interrupt
	j default_handler
	j default_handler
	j default_handler
	j default_handler

