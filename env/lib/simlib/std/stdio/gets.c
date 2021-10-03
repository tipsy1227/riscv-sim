#include <stdio.h>

/* gets: read an entire line from the uart device */
char *gets(char *str){
	int c;
	char *s = str;

	// keep reading until a '\n' or EOF character
	while((c = getchar()) != '\n' && c != EOF)
		*s++ = c;

	if(c == EOF && s == str){ // return NULL string if the first character is EOF
		return NULL;
	} else{
		*s = '\0';
		return str;
	}
}

