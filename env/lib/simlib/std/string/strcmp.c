#include <string.h>

/* strcmp: compare two strings */
int strcmp(const char *s, const char *t){
	while(*s && (*s == *t))
		++s, ++t;

	return *s - *t;
}

