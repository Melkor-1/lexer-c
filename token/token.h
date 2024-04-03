#ifndef TOKEN_H
#define TOKEN_H 1

#include <stddef.h>

#define FOREACH_TOK(_) \
    _(TOK_ILLEGAL)      \
    _(TOK_EOF)          \
    _(TOK_IDENT)        \
    _(TOK_INT)          \
    _(TOK_STRING)       \
    _(TOK_ASSIGN)       \
    _(TOK_PLUS)         \
    _(TOK_MINUS)        \
    _(TOK_BANG)         \
    _(TOK_ASTERISK)     \
    _(TOK_SLASH)        \
    _(TOK_LT)           \
    _(TOK_GT)           \
    _(TOK_EQ)           \
    _(TOK_NOT_EQ)       \
    _(TOK_COMMA)        \
    _(TOK_SEMICOLON)    \
    _(TOK_COLON)        \
    _(TOK_LPAREN)       \
    _(TOK_RPAREN)       \
    _(TOK_LBRACE)       \
    _(TOK_RBRACE)       \
    _(TOK_RBRACKET)     \
    _(TOK_LBRACKET)     \
    _(TOK_FUNCTION)     \
    _(TOK_LET)          \
    _(TOK_TRUE)         \
    _(TOK_FALSE)        \
    _(TOK_IF)           \
    _(TOK_ELSE)         \
    _(TOK_RETURN)       \


typedef enum {
    #define GEN_ENUM_COMMA(ENUM) ENUM,
    FOREACH_TOK(GEN_ENUM_COMMA)
    #undef GEN_ENUM_COMMA
} TokenType;

typedef struct Token {
    TokenType   type;
    const char *lit;
} Token;

TokenType token_lookup_ident(size_t len, const char ident[static len]);
Token token_new(TokenType type, const char lit[static 1]);
void token_delete(Token t);
const char *token_to_str(TokenType t);

#endif /* TOKEN_H */
