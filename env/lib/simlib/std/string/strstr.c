#include <string.h>

/* strstr: locate substring */
char *strstr(const char *s, const char *t){
	size_t len = strlen(t);
	for(; *s; ++s){
		if(!strncmp(s, t, len))
			return (char *)s;
	}
	return NULL;
}

