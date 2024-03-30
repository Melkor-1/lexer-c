#ifndef UTIL_H
#define UTIL_H 1

#include "stdio.h"

char *util_memstr(size_t n, const char s[static n]);
char *util_readline(FILE stream[static 1], size_t len[static 1]);

#endif /* UTIL_H */
