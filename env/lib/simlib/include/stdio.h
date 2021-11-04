#pragma once

#include <stdarg.h>
#include <stddef.h>

#define EOF -1

int getchar(void);
int putchar(int);

char *gets(char *);
int puts(const char *);

int printf(const char *, ...);
int sprintf(char *, const char *, ...);
int snprintf(char *, size_t, const char *, ...);
int vprintf(const char *, va_list);
int vsprintf(char *, const char *, va_list);
int vsnprintf(char *, size_t, const char *, va_list);

int scanf(const char *, ...);
int sscanf(const char *, const char *, ...);
int vscanf(const char *, va_list);
int vsscanf(const char *, const char *, va_list);

int ungetchar(int); // not standard

