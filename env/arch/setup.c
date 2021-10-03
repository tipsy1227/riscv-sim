#include <arch.h>

extern char *_bss_start;
extern char *_bss_end;

/* _arch_setup: to clear bss section and setup hardwares */
void _arch_setup(){
//	memset(_bss_start, 0, _bss_end - _bss_start);
	_uart_init();
	_finisher_init();
}

