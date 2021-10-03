#include <stdio.h>

/* snprintf: write the formated datas to a sized buffer */
int snprintf(char *out, size_t n, const char *fmt, ...){
	int len;
	va_list vl;

	va_start(vl, fmt);
	len = vsnprintf(out, n, fmt, vl);
	va_end(vl);

	return len;
}

