#pragma once

#include <stddef.h>
#include <stdint.h>

int atoi(const char *);
long atol(const char *);
long long atoll(const char *);

int abs(int);
long labs(long);
long long llabs(long long);

__attribute__((noreturn)) void exit(int status);
//__attribute__((noreturn)) void abort(void);

