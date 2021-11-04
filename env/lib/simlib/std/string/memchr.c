#include <string.h>

/* memchr: locate character in block of memory */
void *memchr(const void *p, int c, size_t n){
	for(size_t i = 0; i < n; ++i){
		unsigned char *pp = (unsigned char *)p + i;
		if(*pp == c)
			return pp;
	}
	return NULL;
}

