#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *util_memstr(size_t n, const char s[static n])
{
    char *const p = malloc(n + 1);

    if (p != NULL) {
        memcpy(p, s, n);
        p[n] = '\0';
    }

    return p;
}

char *util_readline(FILE stream[static 1], size_t len[static 1])
{
    size_t count = 0;
    size_t capacity = 0;
    char *line = NULL;

    for (;;) {
        if (count >= capacity) {
            capacity = capacity < BUFSIZ ? BUFSIZ : capacity * 2;
            char *const tmp = realloc(line, capacity + 1);

            if (tmp == NULL) {
                free(line);
                return NULL;
            }

            line = tmp;
        }

        const int c = getc(stream);

        if (c == EOF || c == '\n') {
            if (c == EOF) {
                if (feof(stream)) {
                    if (!count) {
                        free(line);
                        return NULL;
                    }
                    /* Return what was read. */
                    break;
                }
                /* Read error. */
                free(line);
                return NULL;
            } else {
                break;
            }
        } else {
            line[count] = (char) c;
        }
        ++count;
    }
    
    *len = count;
    return line;
}

