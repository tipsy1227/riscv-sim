#include <arch/uart.h>
#include <drivers/ns16550a.h>

__attribute__((weak)) void *uart_start = (void *)0x10000000;

/* uart_init: to setup ns16550a as uart device */
__attribute__((weak)) void uart_init(int baudrate){
	ns16550a_init(uart_start, baudrate);
}

/* uart_read: to read a byte from the uart */
__attribute__((weak)) int uart_read(){
	int c = ns16550a_read();
	if(c == '\r')
		return '\n';
	return c;
}

/* uart_write: to write a byte to the uart */
__attribute__((weak)) int uart_write(int c){
	return ns16550a_write(c);
}

