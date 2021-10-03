#include <stdio.h>

/* puts: write a NULL-terminated string to the uart device and append an newline after it */
int puts(const char *str){
	int c;
	while((c = *str++))
		putchar(c);

	putchar('\n'); // append an newline after str
	return 0;
}

