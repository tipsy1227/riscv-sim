#pragma once

#define max(x, y) ((x) > (y))? (x): (y)
#define min(x, y) ((x) < (y))? (x): (y)

char *_itoa(intmax_t, char *, int);
char *_utoa(uintmax_t, char *, int);

intmax_t _atoi(const char *, int);

