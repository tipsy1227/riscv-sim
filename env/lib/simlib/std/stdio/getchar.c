#include <arch/uart.h>
#include <stdio.h>

enum{
	EOT = 0x04,
};

/* getchar: read a byte from the uart device */
int getchar(){
	int c = uart_read();
	if(c == EOT)
		return EOF;
	return c;
}

