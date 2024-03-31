// TODO: Change the API to hide the lexer's internals.

#include <ctype.h>
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

static int is_letter(char ch)
{
    return ch == '_' || isalpha((unsigned char)ch) != 0;
}

static const char *read_ident(Lexer l[static 1], size_t len[static 1])
{
    const size_t orig_pos = l->pos;
    for (; is_letter(l->ch) != 0; read_char(l)) ;
    *len = l->pos - orig_pos;
    return l->input + orig_pos;
}

static const char *read_int(Lexer l[static 1], size_t len[static 1])
{
    const size_t orig_pos = l->pos;
    for (; isdigit((unsigned char)l->ch) != 0; read_char(l)) ;
    *len = l->pos - orig_pos;
    return l->input + orig_pos;
}

static const char *read_string(Lexer l[static 1], size_t len[static 1])
{
    /* Monkey doesn't support escape characters. 
     * TODO: Perhaps return NULL on EOF. 
     */
    const size_t orig_pos = l->pos + 1;

    do {
        read_char(l);
    } while (l->ch != '"' && l->ch != '\0');

    *len = l->pos - orig_pos;
    return l->input + orig_pos;
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

        case '"': {
            size_t len = 0;
            t.lit = read_string(l, &len);
            t.type = TOK_STRING;
            t.lit = util_memstr(len, t.lit);
        } break;

        default:
            if (is_letter(l->ch) != 0) {
                size_t len = 0;
                t.lit = read_ident(l, &len);
                t.type = token_lookup_ident(len, t.lit);
                t.lit = util_memstr(len, t.lit);
                return t;
            } else if (isdigit((unsigned char)l->ch) != 0) {
                size_t len = 0;
                t.type = TOK_INT;
                t.lit = read_int(l, &len);
                t.lit = util_memstr(len, t.lit);
                return t;
            } 
            t = token_new(TOK_ILLEGAL, util_memstr(1, &l->ch));
    }

    read_char(l);
    return t;
}
