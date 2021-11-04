#include <string.h>

/* memcmp: compare two blocks of memory */
int memcmp(const void *p1, const void *p2, size_t n){
	for(int i = 0; i < n; ++i){
		unsigned char c1 = *((const unsigned char *)p1 + i);
		unsigned char c2 = *((const unsigned char *)p2 + i);
		if(c1 != c2)
			return c1 - c2;
	}
	return 0;
}

