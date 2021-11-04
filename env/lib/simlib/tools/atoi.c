#include <tools.h>
#include <stdint.h>
#include <ctype.h>

intmax_t _atoi(const char *s, int base){
	intmax_t val;
	int sign;
	int c;

	if(base < 2 || base > 36)
		return 0;

	while(isspace(*s))    /* skip white space */
		s++;

	sign = (*s=='-')? -1: 1;
	if(*s=='+' || *s=='-')
		s++;

	for(val=0; _isdigitof(base, c = tolower(*s)); s++)
		val = base * val + ((isdigit(c))? (c - '0'): (c - 'a' + 10));
	return sign * val;
}

