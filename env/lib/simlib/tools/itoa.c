#include <stdlib.h>
#include <string.h>
#include <tools.h>

static void reverse(char s[]){
	int i, j;
	char tmp;
	for(i=0, j=strlen(s)-1; i<j; i++, j--)
		tmp=s[i], s[i]=s[j], s[j]=tmp;    /* swap s[i] and s[j] */
}

/* itoa: convert n to characters in s */
char *_itoa(intmax_t n, char s[], int base){
	size_t i;
	size_t d;
	intmax_t sign;
	if(base < 2 || base > 36)
		return s;

	sign = n;    /* record sign */
	i = 0;
	do{    /* generate digits in reverse order */
		d = abs(n % base);
		s[i++] = (d < 10)? d +'0': d + 'a' - 10;    /* get next digit */
	} while((n/=base) != 0);    /* delete it */
	if(base == 10 && sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);

	return s;
}

