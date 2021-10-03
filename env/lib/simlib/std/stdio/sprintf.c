#include <stdio.h>

/* sprintf: write the formated datas to a buffer */
int sprintf(char *out, const char *fmt, ...){
	int len;
	va_list vl;

	va_start(vl, fmt);
	len = vsprintf(out, fmt, vl);
	va_end(vl);

	return len;
}

