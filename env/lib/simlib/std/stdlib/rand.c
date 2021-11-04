#include <stdlib.h>

static unsigned long long next = 1;

/* rand: return pseudo-random integer on 0..RAND_MAX */
int rand(){
	next = next * 1103515245 + 123456789;
	return (unsigned int)(next/65536) % ((unsigned int)RAND_MAX + 1);
}

/* srand: set seed for rand() */
void srand(unsigned int seed){
	next = seed;
}

