#include <stdio.h>

/* sscanf: read formated data from s */
int sscanf(const char *s, const char *fmt, ...){
	int nc;
	va_list vl;
	
	va_start(vl, fmt);
	nc = vsscanf(s, fmt, vl);
	va_end(vl);

	return nc;
}

