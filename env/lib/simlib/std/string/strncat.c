#include <string.h>

/* strncat: concatenate n character from s to t */
char *strncat(char *t, const char *s, size_t n){
	size_t i, j;
	for(i = 0; t[i]; ++i)
		;
	for(j = 0; j < n && s[j]; ++i, ++j)
		t[i] = s[j];
	t[i] = '\0';
	return t;
}

