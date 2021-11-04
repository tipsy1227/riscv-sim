#include <string.h>

/* strpbrk: locate characters in string */
char *strpbrk(char *s, const char *t){
	for(; *s; ++s){
		for(const char *tt = t; *tt; ++tt){
			if(*s == *tt)
				return s;
		}
	}
	return NULL;
}

