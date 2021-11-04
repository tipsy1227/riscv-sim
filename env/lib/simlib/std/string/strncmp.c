#include <string.h>

/* strncmp: compare n character at most between s and t */
int strncmp(const char *s, const char *t, size_t n){
	size_t i = 0;
	while((i < n - 1) && s[i] && (s[i] == t[i]))
		++i;

	return s[i] - t[i];
}

