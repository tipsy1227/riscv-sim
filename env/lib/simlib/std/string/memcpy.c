#include <string.h>

/* memcpy: copy block of memory */
void *memcpy(void *dst, const void *src, size_t n){
	for(size_t i = 0; i < n; ++i)
		((char *)dst)[i] = ((const char *)src)[i];
	return dst;
}

