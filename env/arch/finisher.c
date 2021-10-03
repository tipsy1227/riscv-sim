#include <arch.h>
#include <stdint.h>
#include "finisher.h"

static volatile uint32_t *finisher_ctrl_ptr;

/* _finisher_init: to setup the sifive_test device */
void _finisher_init(){
	finisher_ctrl_ptr = (uint32_t *)FINISHER_ADDR;
}

/* _finisher_exit: to stop the emulation */
__attribute__((noreturn)) void _finisher_exit(int status){
	if(status != 0){
		*finisher_ctrl_ptr = (uint32_t)(status << 16 | FINISHER_FAIL);
	} else{
		*finisher_ctrl_ptr = (uint32_t)FINISHER_PASS;
	}
	__builtin_unreachable();
}

/* _finisher_reset: to restart the emulation */
__attribute__((noreturn)) void _finisher_reset(){
	*finisher_ctrl_ptr = FINISHER_RESET;
	__builtin_unreachable();
}

