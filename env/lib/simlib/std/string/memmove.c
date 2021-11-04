#include <string.h>

/* memmove: move block of memory */
void *memmove(void *dst, const void *src, size_t n){
	if(dst + n > src){
		for(size_t i = n-1; i > 0; --i)
			((char *)dst)[i] = ((const char *)src)[i];
		((char *)dst)[0] = ((char *)src)[0];
	} else{
		for(size_t i = 0; i < n; ++i)
			((char *)dst)[i] = ((const char *)src)[i];
	}
	return dst;
}

