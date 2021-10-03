#include <stdio.h>

/* printf: write formatted datas to stdout */
int printf(const char * fmt, ...){
	int len;
	va_list vl;

	va_start(vl, fmt);
	len = vprintf(fmt, vl);
	va_end(vl);

	return len;
}

