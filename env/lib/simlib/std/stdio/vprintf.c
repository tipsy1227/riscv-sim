#include <stdio.h>

/* vprintf: write formatted datas from variable argument list to stdout */
int vprintf(const char * fmt, va_list vl){
	int len = vsnprintf(NULL, 0, fmt, vl);

	char out[len + 1];
	vsprintf(out, fmt, vl);

	for(int i = 0; i < len; ++i)
		putchar(out[i]);
	return len;
}

