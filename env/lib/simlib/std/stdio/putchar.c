#include <arch/uart.h>
#include <stdio.h>

/* putchar: write a byte to the uart device */
int putchar(int c){
	return uart_write(c);
}

