#include <stdlib.h>
#include <ctype.h>

/* atol: convert an integer string to its long integer value */
long atol(const char *s){
	long val;
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

