#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "../token/token.h"
#include "../util/util.h"

static void read_char(Lexer l[static 1])
{
    l->ch = l->read_pos >= l->input_len ? '\0' : l->input[l->read_pos];
    l->pos = l->read_pos;
    ++l->read_pos;
}

static char peek_char(Lexer l)
{
    return l.read_pos >= l.input_len ? '\0' : l.input[l.read_pos];
}

static bool is_letter(char ch)
{
    return ch == '_' || isalpha((unsigned char)ch) != 0;
}

static Token read_ident(Lexer l[static 1])
{
    const size_t orig_pos = l->pos;
    for (; is_letter(l->ch) != 0; read_char(l)) ;
    return (Token) {
        .type = token_lookup_ident(l->pos - orig_pos, l->input + orig_pos ),
        .lit = util_memstr(l->pos - orig_pos, l->input + orig_pos)
    };
}

static Token read_int(Lexer l[static 1])
{
    const size_t orig_pos = l->pos;
    for (; isdigit((unsigned char)l->ch) != 0; read_char(l)) ;
    return  (Token) {
        .type = TOK_INT,
        .lit = util_memstr(l->pos - orig_pos, l->input + orig_pos)
    };

}

static Token read_string(Lexer l[static 1])
{
    /* Monkey doesn't support escape characters.  */
    const size_t orig_pos = l->pos + 1;
    do {
        read_char(l);
    } while (l->ch != '"' && l->ch != '\0');
    
    if (l->ch == '\0') {
        return (Token) {
            .type = TOK_ILLEGAL,
            .lit = util_memstr(l->pos - orig_pos, l->input + orig_pos)
        };
    }

    read_char(l);
    return (Token) {
        .type = TOK_STRING,
        .lit = util_memstr(l->pos - orig_pos - 1, l->input + orig_pos)
    };
}

static void skip_whitespace(Lexer l[static 1])
{
    for (; isspace((unsigned char)l->ch) != 0; read_char(l)) ;
}

Lexer lexer_new(const char input[static 1])
{
    Lexer l = {
        .input = input,
        .input_len = strlen(input),
    };
    read_char(&l);
    return l;
}

Token lexer_next(Lexer l[static 1])
{
    Token t;
    skip_whitespace(l);

    switch (l->ch) {
        case '=':
            if (peek_char(*l) == '=') {
                read_char(l);
                t = token_new(TOK_EQ, "==");
            } else {
                t = token_new(TOK_ASSIGN, "=");
            }
            break;

        case '+':
            t = token_new(TOK_PLUS, "+");
            break;

        case '-':
            t = token_new(TOK_MINUS, "-");
            break;

        case '*':
            t = token_new(TOK_ASTERISK, "*");
            break;

        case '/':
            t = token_new(TOK_SLASH, "/");
            break;

        case '!':
            if (peek_char(*l) == '=') {
                read_char(l);
                t = token_new(TOK_NOT_EQ, "!=");
            } else {
                t = token_new(TOK_BANG, "!");
            }
            break;

        case '<':
            t = token_new(TOK_LT, "<");
            break;

        case '>':
            t = token_new(TOK_GT, ">");
            break;

        case ',':
            t = token_new(TOK_COMMA, ",");
            break;

        case ';':
            t = token_new(TOK_SEMICOLON, ";");
            break;

        case ':':
            t = token_new(TOK_COLON, ":");
            break;

        case '(':
            t = token_new(TOK_LPAREN, "(");
            break;

        case ')':
            t = token_new(TOK_RPAREN, ")");
            break;

        case '{':
            t = token_new(TOK_LBRACE, "{");
            break;

        case '}':
            t = token_new(TOK_RBRACE, "}");
            break;

        case '[':
            t = token_new(TOK_LBRACKET, "[");
            break;

        case ']':
            t = token_new(TOK_RBRACKET, "]");
            break;

        case '\0':
            t = token_new(TOK_EOF, "");
            break;

        case '"': 
            return read_string(l);

        default:
            if (is_letter(l->ch) != 0) {
                return read_ident(l);
            } else if (isdigit((unsigned char)l->ch) != 0) {
                return read_int(l);
            } 
            t = token_new(TOK_ILLEGAL, util_memstr(1, &l->ch));
    }

    read_char(l);
    return t;
}
