#include <stdlib.h>

/* bsearch: find key from the array base of size n */
void *bsearch(const void *key, const void *base, size_t n,
	size_t size, int (*compar)(const void *, const void *)){
	size_t low, high, mid;

	low = 0;
	high = n - 1;
	while(low < high){
		mid = (low + high) / 2;
		if(compar(key, (char *)base + mid * size) > 0)
			low = mid + 1;
		else
			high = mid;
	}

	return (compar(key, (char *)base + low * size))? NULL: (char *)base + low * size;
}

