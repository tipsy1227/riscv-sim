#include <string.h>

/* strcat: concatennate s to the end of t */
char *strcat(char *t, const char *s){
	char *tt;
	for(tt = t; *tt; ++tt)
		;
	while(*s)
		*tt++ = *s++;
	*tt = '\0';
	return t;
}

