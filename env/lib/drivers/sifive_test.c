#include <drivers/sifive_test.h>
#include <stdint.h>

enum {
	SIFIVE_TEST_FAIL  = 0x3333,  /* FAIL code of SIFIVE_TEST */
	SIFIVE_TEST_PASS  = 0x5555,  /* PASS code of SIFIVE_TEST */
	SIFIVE_TEST_RESET = 0x7777,  /* RESET code of SIFIVE_TEST */
};

static volatile uint32_t *sifive_test_ctrl_ptr;

/* sifive_test_init: to setup the sifive_test device */
__attribute__((weak)) void sifive_test_init(void *sifive_test_start){
	sifive_test_ctrl_ptr = (uint32_t *)sifive_test_start;
}

/* sifive_test_exit: to stop the emulation */
__attribute__((noreturn, weak)) void sifive_test_exit(int status){
	if(status != 0){
		*sifive_test_ctrl_ptr = (uint32_t)(status << 16 | SIFIVE_TEST_FAIL);
	} else{
		*sifive_test_ctrl_ptr = (uint32_t)SIFIVE_TEST_PASS;
	}
	__builtin_unreachable();
}

/* sifive_test_reset: to restart the emulation */
__attribute__((noreturn, weak)) void sifive_test_reset(){
	*sifive_test_ctrl_ptr = SIFIVE_TEST_RESET;
	__builtin_unreachable();
}

