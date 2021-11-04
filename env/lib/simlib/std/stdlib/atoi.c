#include <stdlib.h>
#include <tools.h>

/* atoi: convert an integer string to its integer value */
int atoi(const char *s){
	return _atoi(s, 10);
}

/* atol: convert an integer string to its long integer value */
long atol(const char *s){
	return _atoi(s, 10);
}

/* atoll: convert an integer string to its long long integer value */
long long atoll(const char *s){
	return _atoi(s, 10);
}

