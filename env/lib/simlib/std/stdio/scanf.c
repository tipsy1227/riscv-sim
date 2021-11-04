#include <stdio.h>

/* scanf: read formated data from stdio */
int scanf(const char *fmt, ...){
	int nc;
	va_list vl;
	
	va_start(vl, fmt);
	nc = vscanf(fmt, vl);
	va_end(vl);

	return nc;
}

