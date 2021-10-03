#include <stdint.h>
#include <ctype.h>
#include <tools.h>

static int isdigitof(int base, char c){
	if(base < 10){
		return c >= '0' && c < '0' + base;
	} else{
		return isdigit(c) || (c >= 'a' && c < 'a' + base);
	}
}

intmax_t _atoi(const char *s, int base){
	intmax_t val;
	int sign;
	int c;

	if(base < 2 || base > 36)
		return 0;

	while(isspace(*s))    /* skip white space */
		s++;

	if(base == 10){
		sign = (*s=='-')? -1: 1;
		if(*s=='+' || *s=='-')
			s++;
	} else
		sign = 1;

	for(val=0; isdigitof(base, c = tolower(*s)); s++)
		val = base * val + ((isdigit(c))? (c - '0'): (c - 'a' + 10));
	return sign * val;
}

