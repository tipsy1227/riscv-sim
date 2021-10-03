#include <string.h>

/* strlen: return length of s */
size_t strlen(const char *s){
	int i = 0;
	while(s[i] != '\0')
		++i;
	return i;
}

