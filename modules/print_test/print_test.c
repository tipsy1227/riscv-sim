#include <arch.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <tools.h>

int main(){

	// tests for decimal specifier
	printf("tests for decimal number\n");
	printf("-------------------------------------------------------\n");
	printf("%%d: %d\n", 12345);
	printf("%%10d: %10d\n", -12345);
	printf("%%3d: %3d\n", 12345);
	printf("%%+10d: %+10d\n", -12345);
	printf("%%+3d: %+3d\n", 12345);
	printf("%% 10d: % 10d\n", -12345);
	printf("%% 3d: % 3d\n", 12345);
	printf("%%-10d: %-10d\n", -12345);
	printf("%%-3d: %-3d\n", 12345);
	printf("%%+010d: %+010d\n", -12345);
	printf("%%+03d: %+03d\n", 12345);
	printf("-------------------------------------------------------\n");

	// tests for unsigned specifier
	printf("tests for unsigned decimal number\n");
	printf("-------------------------------------------------------\n");
	printf("%%u: %u\n", 12345);
	printf("%%10u: %10u\n", 12345);
	printf("%%3u: %3u\n", 12345);
	printf("%%-10u: %-10u\n", 12345);
	printf("%%-3u: %-3u\n", 12345);
	printf("%%010u: %010u\n", 12345);
	printf("%%03u: %03u\n", 12345);
	printf("-------------------------------------------------------\n");

	// tests for octal specifier
	printf("tests for octal number\n");
	printf("-------------------------------------------------------\n");
	printf("%%o: %o\n", 077777);
	printf("%%10o: %10o\n", 077777);
	printf("%%3o: %3o\n", 077777);
	printf("%%-10o: %-10o\n", 077777);
	printf("%%-3o: %-3o\n", 077777);
	printf("%%#10o: %#10o\n", 077777);
	printf("%%#3o: %#3o\n", 077777);
	printf("%%#010o: %#010o\n", 077777);
	printf("%%#03o: %#03o\n", 077777);
	printf("%%.10o: %.10o\n", 077777);
	printf("%%.3o: %.3o\n", 077777);
	printf("%%#.10o: %#.10o\n", 077777);
	printf("%%#.3o: %#.3o\n", 077777);
	printf("-------------------------------------------------------\n");

	// tests for hex specifier
	printf("tests for hexidecimal number\n");
	printf("-------------------------------------------------------\n");
	printf("%%X: %X\n", 0xaaaaa);
	printf("%%10X: %10X\n", 0xaaaaa);
	printf("%%3x: %3x\n", 0xaaaaa);
	printf("%%-10X: %-10X\n", 0xaaaaa);
	printf("%%-3x: %-3x\n", 0xaaaaa);
	printf("%%#10X: %#10X\n", 0xaaaaa);
	printf("%%#3x: %#3x\n", 0xaaaaa);
	printf("%%#010X: %#010X\n", 0xaaaaa);
	printf("%%#03x: %#03x\n", 0xaaaaa);
	printf("%%.10X: %.10X\n", 0xaaaaa);
	printf("%%.3x: %.3x\n", 0xaaaaa);
	printf("%%#.10X: %#.10X\n", 0xaaaaa);
	printf("%%#.3x: %#.3x\n", 0xaaaaa);
	printf("-------------------------------------------------------\n");

	// tests for string specifier
	printf("tests for string\n");
	printf("-------------------------------------------------------\n");
	printf("%%s: %s\n", "Hello");
	printf("%%10s: %10s\n", "Hello");
	printf("%%3s: %3s\n", "Hello");
	printf("%%-10s: %-10s\n", "Hello");
	printf("%%-3s: %3s\n", "Hello");
	printf("%%.10s: %.10s\n", "Hello");
	printf("%%.3s: %.3s\n", "Hello");
	printf("-------------------------------------------------------\n");

	// tests for char specifier
	printf("tests for char\n");
	printf("-------------------------------------------------------\n");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '!');
	printf("-------------------------------------------------------\n");

	// tests for pointer specifier
	printf("tests for pointer\n");
	printf("-------------------------------------------------------\n");
	printf("%%p: %p\n", (void *)0xaaaaa);
	printf("%%10p: %10p\n", (void *)0xaaaaa);
	printf("%%3p: %3p\n", (void *)0xaaaaa);
	printf("%%-10p: %-10p\n", (void *)0xaaaaa);
	printf("%%-3p: %-3p\n", (void *)0xaaaaa);
	printf("-------------------------------------------------------\n");

	return 0;
}
