#include <stdlib.h>
#include <string.h>

static void swap(void *base, size_t size, size_t i, size_t j){
	char tmp[size];
	memcpy(tmp, (char *)base + i * size, size);
	memcpy((char *)base + i * size, (char *)base + j * size, size);
	memcpy((char *)base + j * size, tmp, size);
}

/* qsort: sort elemets of array */
void qsort(void *base, size_t n, size_t size, int (*comp)(const void *, const void *)){
	size_t last;

	if(n <= 1) // do nothing if array contains fewer than two elements
		return;
	last = 0;
	for(size_t i = 1; i < n; ++i){ // use the first element to partition
		if(comp((char *)base + i * size, (char *)base) < 0)
			swap(base, size, ++last, i);
	}
	swap(base, size, 0, last); // restore partition element
	qsort((char *)base, last, size, comp); // sort the left part
	qsort((char *)base + (last+1) * size, n - last - 1, size, comp); // sort the right part
}

