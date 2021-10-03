#include <arch.h>
#include <stdio.h>

/* putchar: write a byte to the uart device */
int putchar(int c){
	return _uart_write(c);
}

