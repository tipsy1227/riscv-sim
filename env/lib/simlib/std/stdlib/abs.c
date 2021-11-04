#include <stdlib.h>

/* abs: convert an integer to its absolute value */
int abs(int n){
	return (n < 0)? -n: n;
}

/* labs: convert an long integer n to its absolute value */
long labs(long n){
	return (n < 0)? -n: n;
}

/* llabs: convert an long long integer n to its absolute value */
long long llabs(long long n){
	return (n < 0)? -n: n;
}

