#include "timer.h"

static char *uart_ctrl_ptr = (char *)0x10000000; // address of UART device
int divisor = 1; // divisor for 399193 baud

/* main: uart example with exit routine */
void uart_setup(){
	// setup UART to be 399193 baud, 8 bit transmission, and with odd parity
	uart_ctrl_ptr[LCR] = LCR_DLAB;
	uart_ctrl_ptr[DLO] = divisor & 0xff;
	uart_ctrl_ptr[DUP] = (divisor >> 8) & 0xff;
	uart_ctrl_ptr[LCR] = LCR_8BIT | LCR_PODD;
}

