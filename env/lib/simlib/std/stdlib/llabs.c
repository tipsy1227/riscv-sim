#include <stdlib.h>

/* llabs: convert an long long integer n to its absolute value */
long long llabs(long long n){
	return (n < 0)? -n: n;
}

