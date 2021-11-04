#pragma once

#include <stdint.h>

#define max(x, y) ((x) > (y))? (x): (y)
#define min(x, y) ((x) < (y))? (x): (y)

int _isdigitof(int, int);

char *_itoa(intmax_t, char *, int);
char *_utoa(uintmax_t, char *, int);

intmax_t _atoi(const char *, int);

