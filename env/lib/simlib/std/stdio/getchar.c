#include <arch.h>
#include <stdio.h>

/* getchar: read a byte from the uart device and change '\r' to '\n' before return it */
int getchar(){
	int c;
	if((c = _uart_read()) == '\r')
		return '\n';
	return c;
}

