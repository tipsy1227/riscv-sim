#include <stdlib.h>
#include <ctype.h>

/* atoll: convert an integer string to its long long integer value */
long long atoll(const char *s){
	long long val;
	int sign;

	while(isspace(*s))    /* skip white space */
		s++;
	sign = (*s=='-')? -1: 1;
	if(*s=='+' || *s=='-')
		s++;
	for(val=0; isdigit(*s); s++)
		val = 10*val+(*s-'0');
	return sign * val;
}

