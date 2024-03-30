#include "token.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GEN_STR(STR) #STR,

static const char *const tok_strs[] = {
    FOREACH_TOK(GEN_STR)
};

static const size_t tok_strs_count = sizeof tok_strs / sizeof *tok_strs;

const char *token_to_str(TokenType t)
{
    return t < 0 || t > tok_strs_count ? NULL : tok_strs[t];
}

TokenType token_lookup_ident(size_t len, const char ident[static len])
{
    static struct keyword {
        const char *const kw;
        TokenType kw_type;
    } const kws[] = {
        { "fn",     TOK_FUNCTION },
        { "let",    TOK_LET      },
        { "true",   TOK_TRUE     },
        { "false",  TOK_FALSE    },
        { "if",     TOK_IF       },
        { "else",   TOK_ELSE     },
        { "return", TOK_RETURN   },
    };

    static const size_t kws_count = sizeof kws / sizeof kws[0];

    for (size_t i = 0; i < kws_count; ++i) {
        if (strncmp(ident, kws[i].kw, len) == 0) {
            return kws[i].kw_type;
        }
    }

    return TOK_IDENT;
}

Token token_new(TokenType type, const char lit[static 1])
{
    return (Token) {
        .type = type,
        .lit = lit,
    };
}

static bool is_kw(TokenType t)
{
    static const TokenType kws[] = {
        TOK_FUNCTION,
        TOK_LET,
        TOK_TRUE,
        TOK_FALSE,
        TOK_IF,
        TOK_ELSE,
        TOK_RETURN,
    };

    return memchr(kws, t, sizeof kws) != NULL;
}

static bool is_dynamic_alloc(TokenType t)
{
    return (t == TOK_INT   
            || t == TOK_ILLEGAL 
            || t == TOK_IDENT
            || is_kw(t));
}

void token_delete(Token t)
{
    if (is_dynamic_alloc(t.type)) {
        free((char *)t.lit);
    }
}
