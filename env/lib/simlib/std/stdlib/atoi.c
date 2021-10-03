#include <stdlib.h>
#include <ctype.h>

/* atoi: convert an integer string to its integer value */
int atoi(const char *s){
	int val;
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

