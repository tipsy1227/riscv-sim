#include <arch/finisher.h>
#include <drivers/sifive_test.h>

__attribute__((weak)) void *finisher_start = (void *)0x100000;

/* finisher_init: setup sifive_test as a finisher */
__attribute__((weak)) void finisher_init(){
	sifive_test_init(finisher_start);
}

/* finisher_exit: to stop the emulation */
__attribute__((weak)) void finisher_exit(int status){
	sifive_test_exit(status);
}

/* finisher_reset: to restart the emulation */
__attribute__((weak)) void finisher_reset(){
	sifive_test_reset();
}

