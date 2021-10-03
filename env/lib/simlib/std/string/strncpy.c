#include <string.h>

/* strncpy: copies at most n characters of s to t */
char *strncpy(char *t, const char *s, size_t n){
	size_t i;

	for(i = 0; i < n && s[i] !='\0'; i++)
		t[i] = s[i];

	// pad with zeros till a total of n characters have benn copied
	while(i < n)
		t[i++] = '\0';

	return t;
}

