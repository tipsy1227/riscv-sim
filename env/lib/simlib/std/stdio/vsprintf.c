#include <stdio.h>
#include <limits.h>

/* vsprintf: write formatted datas from variable argument list to a lagrge enough buffer */
int vsprintf (char *out, const char * fmt, va_list vl){
	return vsnprintf(out, INT_MAX, fmt, vl);
}

