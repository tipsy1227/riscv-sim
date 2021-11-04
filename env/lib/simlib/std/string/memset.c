#include <string.h>

/* memset: fill block of memory */
void *memset(void *p, int c, size_t n){
	for(size_t i = 0; i < n; ++i)
		((char *)p)[i] = c;
	return p;
}

