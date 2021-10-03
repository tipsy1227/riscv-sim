#include <arch.h>
#include <stdint.h>
#include "uart.h"

static volatile uint8_t *uart_ctrl_ptr;
static volatile uint32_t divisor;

/* _uart_init: to setup ns16550a uart device */
void _uart_init(){
	uart_ctrl_ptr = (uint8_t *)UART_ADDR;
	divisor = (uint32_t)(UART_CLOCKRATE / (16 * BAUD_RATE));
	uart_ctrl_ptr[UART_LCR] = UART_LCR_DLAB;
	uart_ctrl_ptr[UART_DLL] = divisor & 0xff;
	uart_ctrl_ptr[UART_DLM] = (divisor >> 8) & 0xff;
    uart_ctrl_ptr[UART_LCR] = UART_LCR_PODD | UART_LCR_8BIT;
}

/* _uart_read: to read a byte from the uart */
int _uart_read(){
	// wait for the data is available
	while(!(uart_ctrl_ptr[UART_LSR] & UART_LSR_DA))
		;

	return uart_ctrl_ptr[UART_RBR];
}

int _uart_write(int c){
	// wait for the line is idle 
	while (!(uart_ctrl_ptr[UART_LSR] & UART_LSR_RI))
		;

	return uart_ctrl_ptr[UART_THR] = c & 0xff;
}

