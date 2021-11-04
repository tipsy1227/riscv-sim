#include <string.h>

/* strrchr: locate last occurrence of character in s */
char *strrchr(const char *s, int c){
	char *ss = (char *)s;
	while(*ss)
		++ss;
	for(; ss >= s; --ss){
		if(*ss == c)
			return ss;
	}
	return NULL;
}

