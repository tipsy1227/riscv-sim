#include <string.h>
#include <stdbool.h>

/* strspn: get span of character set t from s */
size_t strspn(const char *s, const char *t){
	size_t i;
	for(i = 0; s[i]; ++i){
		bool span = false;
		for(size_t j = 0; t[j]; ++j){
			if(s[i] == t[j])
				span = true;
		}
		if(!span)
			return i;
	}
	return i;
}

