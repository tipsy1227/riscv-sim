#include <ctype.h>

/* toupper: convert a lowercase letter to uppercase */
int toupper(int c){
	if(!islower(c))
		return c;
	return c + ('A' - 'a');
}

