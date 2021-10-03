#include <stdlib.h>
#include <string.h>
#include <tools.h>

static void reverse(char s[]){
	int i, j;
	char tmp;
	for(i=0, j=strlen(s)-1; i<j; i++, j--)
		tmp=s[i], s[i]=s[j], s[j]=tmp;    /* swap s[i] and s[j] */
}

/* utoa: convert n to characters in s */
char *_utoa(uintmax_t n, char s[], int base){
	unsigned int i;
	unsigned int d;
	i = 0;
	do{    /* generate digits in reverse order */
		d = n % base;
		s[i++] = (d < 10)? d +'0': d + 'a' - 10;    /* get next digit */
	} while((n/=base) != 0);    /* delete it */
	s[i] = '\0';
	reverse(s);

	return s;
}

