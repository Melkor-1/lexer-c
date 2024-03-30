#ifndef LEXER_H
#define LEXER_H 1

#include "../token/token.h"

// This shouldn't need to be here. No client needs to learn the internals.
// How do we change the API to fix this?
typedef struct lexer {
    const char *input;
    size_t      input_len;
    size_t      pos;        /* Current position in input (points to current char). */
    size_t      read_pos;   /* Current reading position in input (after current char). */
    char        ch;         /* Current char under examination. */
} Lexer;

Lexer lexer_new(const char input[static 1]);
Token lexer_next(Lexer l[static 1]);

#endif /* LEXER_H */
