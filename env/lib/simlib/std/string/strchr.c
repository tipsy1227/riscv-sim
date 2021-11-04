#include <string.h>

/* strchr: locate first occurrence of character in s */
char *strchr(const char *s, int c){
	while(*s && (*s != c))
		++s;
	return (*s == c)? (char *)s: NULL;
}

