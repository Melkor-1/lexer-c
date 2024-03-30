#ifndef TOKEN_H
#define TOKEN_H 1

#include <stddef.h>

#define FOREACH_TOK(_) \
    _(TOK_ILLEGAL)      \
    _(TOK_EOF)          \
    _(TOK_IDENT)        \
    _(TOK_INT)          \
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
    _(TOK_LPAREN)       \
    _(TOK_RPAREN)       \
    _(TOK_LBRACE)       \
    _(TOK_RBRACE)       \
    _(TOK_FUNCTION)     \
    _(TOK_LET)          \
    _(TOK_TRUE)         \
    _(TOK_FALSE)        \
    _(TOK_IF)           \
    _(TOK_ELSE)         \
    _(TOK_RETURN)       \

#define GEN_ENUM(ENUM) ENUM,

typedef enum {
    FOREACH_TOK(GEN_ENUM)
} TokenType;

/* typedef enum { */
/*     TOK_ILLEGAL, */
/*     TOK_EOF, */

/*     /1* Identifiers + literals *1/ */
/*     TOK_IDENT,  /1* add, foobar, x, y, ... *1/ */
/*     TOK_INT,    /1* 1039012 *1/ */
    
/*     /1* Operators *1/ */
/*     TOK_ASSIGN, */ 
/*     TOK_PLUS, TOK_MINUS, TOK_BANG, TOK_ASTERISK, TOK_SLASH, */
/*     TOK_LT, TOK_GT, */
/*     TOK_EQ, TOK_NOT_EQ, */

/*     /1* Delimiters *1/ */
/*     TOK_COMMA, TOK_SEMICOLON, */
/*     TOK_LPAREN, TOK_RPAREN, */ 
/*     TOK_LBRACE, TOK_RBRACE, */

/*     /1* Keywords *1/ */
/*     TOK_FUNCTION, TOK_LET, TOK_TRUE, TOK_FALSE, TOK_IF, TOK_ELSE, TOK_RETURN, */ 
/* } TokenType; */

typedef struct Token {
    TokenType   type;
    const char *lit;
} Token;

TokenType token_lookup_ident(size_t len, const char ident[static len]);
Token token_new(TokenType type, const char lit[static 1]);
void token_delete(Token t);
const char *token_to_str(TokenType t);

#endif /* TOKEN_H */
