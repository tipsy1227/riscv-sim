#include <string.h>

/* strcspn: get span until character in string */
size_t strcspn(const char *s, const char *t){
	size_t i;
	for(i = 0; s[i]; ++i){
		for(size_t j = 0; t[j]; ++j){
			if(s[i] == t[j])
				return i;
		}
	}
	return i;
}

