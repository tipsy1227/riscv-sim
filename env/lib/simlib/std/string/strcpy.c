#include <string.h>

/* strcpy: copies characters of s to t */
char *strcpy(char *t, const char *s){
	while(*s){
		*t = *s;
		++t, ++s;
	}
	*t = '\0';
	return t;
}

