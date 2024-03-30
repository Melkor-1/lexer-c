#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../util/util.h"

int main(void)
{
    printf("Hello! This is the Monkey Programming Language!\n"
            "Type in commands:\n");

    while (true) {
        fputs(">> ", stdout);

        size_t len = 0;
        char *const line = util_readline(stdin, &len);

        if (line == NULL) {
            if (feof(stdin)) {
                break;
            } else {
                fprintf(stderr, "error: an unexpected error occured.\n");
                return EXIT_FAILURE;
            }
        }
        len[line] = '\0';
        Lexer l = lexer_new(line);

        for (Token t = lexer_next(&l); t.type != TOK_EOF; token_delete(t), t = lexer_next(&l)) {
            printf("{Type: %s, Literal: %s}\n", token_to_str(t.type), t.lit);
        }
        free(line);
    }

    return EXIT_SUCCESS;
}
