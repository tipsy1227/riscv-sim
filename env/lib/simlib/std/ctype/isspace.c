#include <ctype.h>

/* isspace: check if c is a space */
int isspace(int c){
	return c == ' ' || c == '\t' || c == '\n' || \
	  c == '\v' || c == '\f' || c == '\r';
}

