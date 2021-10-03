#include <ctype.h>

/* tolower: convert an uppercase letter to lowercase */
int tolower(int c){
	if(!isupper(c))
		return c;
	return c + ('a' - 'A');
}

