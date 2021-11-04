#pragma once

#include <stddef.h> // for size_t and NULL
#include <limits.h>

#define RAND_MAX INT_MAX

#define EXIT_FAILURE 255
#define EXIT_SUCCESS   0

int atoi(const char *);
long atol(const char *);
long long atoll(const char *);

int abs(int);
long labs(long);
long long llabs(long long);

int rand();
void srand(unsigned int);

void *bsearch(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));
void qsort(void *, size_t, size_t, int (*)(const void *, const void *));

__attribute__((noreturn)) void exit(int status);
__attribute__((noreturn)) void _Exit(int status);
__attribute__((noreturn)) void abort(void);

