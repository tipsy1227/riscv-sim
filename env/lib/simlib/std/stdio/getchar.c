#include <stdio.h>
#include <arch/csr.h>
#include <arch/uart.h>

#define BUFSIZE 128

enum{
	EOT = 0x04,
};

char buf[BUFSIZE]; // buffer for getchar/ungetchar
int bufp = 0;      // next free position in buf

/* getchar: read a byte from the uart device */
int getchar(){
	int c;
	if(bufp > 0){
		int tmp = csr_clear(mstatus, MSTAT_MIE); // enter critical section
		c = buf[--bufp];
		csr_write(mstatus, tmp); // exit from critical section
	} else{
		if((c=uart_read()) == EOT)
			c = EOF;
	}
	return c;
}

/* ungetchar: push character back on input (non-standard) */
int ungetchar(int c){
	if(bufp >= BUFSIZE)
		return EOF;
	else{
		int tmp = csr_clear(mstatus, MSTAT_MIE); // enter critical section
		buf[bufp++] = c;
		csr_write(mstatus, tmp); // exit from critical section
		return c;
	}
}
