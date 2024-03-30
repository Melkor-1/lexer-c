#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/lexer.h"
#include "../token/token.h"

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #include <stdnoreturn.h>
#elif defined(__GNUC__) || defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
    #define noreturn        __attribute__((noreturn))
#else
    #define noreturn        /**/
#endif 

typedef struct {
    const TokenType   expected_type;
    const char *const expected_lit;
} test;

static size_t tests_run = 0;

static noreturn void fatal(const char fmt[static 1], ...) 
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    putchar('\n');
    va_end(ap);
    exit(EXIT_FAILURE);
}

static void run_test(const char input[static 1], 
                     const test tests[static 1])
{
    ++tests_run;
    fprintf(stderr, "[INFO]: Running test suite %zu...\n", tests_run);
    Lexer l = lexer_new(input);

    for (const test *p_tests = tests; p_tests->expected_lit != NULL; ++p_tests) {
        const Token t = lexer_next(&l);

        if (t.lit == NULL) {
            fprintf(stderr, "[FAIL]: error: failed to allocate memory for token.\n");
            exit(EXIT_FAILURE);
        }

        const test tt = *p_tests;

        if (t.type != tt.expected_type) {
            fatal("[FAIL]: tests[%zu] - Tokentype wrong. Expected '%s', Got '%s'.\n",
                 p_tests - tests, token_to_str(tt.expected_type), token_to_str(t.type));
        }

        if (strcmp(t.lit, tt.expected_lit) != 0) {
            fatal("[FAIL]: tests[%zu] - Literal wrong. Expected '%s', Got '%s'.\n",
                 p_tests - tests, tt.expected_lit, t.lit);
        }

        token_delete(t);
    }

    fprintf(stderr, "[INFO]: All tests passed!\n");
}

int main(void)
{
    run_test("=+(){},;#", (const test[]) {
        { TOK_ASSIGN,    "=" },
        { TOK_PLUS,      "+" },
        { TOK_LPAREN,    "(" },
        { TOK_RPAREN,    ")" },
        { TOK_LBRACE,    "{" },
        { TOK_RBRACE,    "}" },
        { TOK_COMMA,     "," },
        { TOK_SEMICOLON, ";" },
        { TOK_ILLEGAL,   "#" },
        { TOK_EOF,       ""  },
        { -1,            NULL},
    });

    run_test("let five = 5;"
            "let ten = 10;"
            "let add = fn(x, y) { x + y; };"
            "let result = add(five, ten);",
            (const test[]) {
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "five"  },
        { TOK_ASSIGN,       "="     },
        { TOK_INT,          "5"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "ten"   },
        { TOK_ASSIGN,       "="     },
        { TOK_INT,          "10"    },
        { TOK_SEMICOLON,    ";"     },
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "add"   },
        { TOK_ASSIGN,       "="     },
        { TOK_FUNCTION,     "fn"    },
        { TOK_LPAREN,       "("     },
        { TOK_IDENT,        "x"     },
        { TOK_COMMA,        ","     },
        { TOK_IDENT,        "y"     },
        { TOK_RPAREN,       ")"     },
        { TOK_LBRACE,       "{"     },
        { TOK_IDENT,        "x"     },
        { TOK_PLUS,         "+"     },
        { TOK_IDENT,        "y"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_RBRACE,       "}"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "result"},
        { TOK_ASSIGN,       "="     },
        { TOK_IDENT,        "add"   },
        { TOK_LPAREN,       "("     },
        { TOK_IDENT,        "five"  },
        { TOK_COMMA,        ","     },
        { TOK_IDENT,        "ten"   },
        { TOK_RPAREN,       ")"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_EOF,          ""      },
        { -1,               NULL    },
    });

    run_test("let five = 5;"
            "let ten = 10;"
            "let add = fn(x, y) {"
            "x + y;"
            "};"
            "let result = add(five, ten);"
            "!-/*5;"
            "5 < 10 > 5;"
            "if (5 < 10) {"
            "return true;"
            "} else {"
            "return false;"
            "}"
            "10 == 10;"
            "10 != 9;",
            (const test[]) {
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "five"  },
        { TOK_ASSIGN,       "="     },
        { TOK_INT,          "5"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "ten"   },
        { TOK_ASSIGN,       "="     },
        { TOK_INT,          "10"    },
        { TOK_SEMICOLON,    ";"     },
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "add"   },
        { TOK_ASSIGN,       "="     },
        { TOK_FUNCTION,     "fn"    },
        { TOK_LPAREN,       "("     },
        { TOK_IDENT,        "x"     },
        { TOK_COMMA,        ","     },
        { TOK_IDENT,        "y"     },
        { TOK_RPAREN,       ")"     },
        { TOK_LBRACE,       "{"     },
        { TOK_IDENT,        "x"     },
        { TOK_PLUS,         "+"     },
        { TOK_IDENT,        "y"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_RBRACE,       "}"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_LET,          "let"   },
        { TOK_IDENT,        "result"},
        { TOK_ASSIGN,       "="     },
        { TOK_IDENT,        "add"   },
        { TOK_LPAREN,       "("     },
        { TOK_IDENT,        "five"  },
        { TOK_COMMA,        ","     },
        { TOK_IDENT,        "ten"   },
        { TOK_RPAREN,       ")"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_BANG,         "!"     },
        { TOK_MINUS,        "-"     },
        { TOK_SLASH,        "/"     },
        { TOK_ASTERISK,     "*"     },
        { TOK_INT,          "5"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_INT,          "5"     },
        { TOK_LT,           "<"     },
        { TOK_INT,          "10"    },
        { TOK_GT,           ">"     },
        { TOK_INT,          "5"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_IF,           "if"    },
        { TOK_LPAREN,       "("     },
        { TOK_INT,          "5"     },
        { TOK_LT,           "<"     },
        { TOK_INT,          "10"    },
        { TOK_RPAREN,       ")"     },
        { TOK_LBRACE,       "{"     },
        { TOK_RETURN,       "return"},
        { TOK_TRUE,         "true"  },
        { TOK_SEMICOLON,    ";"     },
        { TOK_RBRACE,       "}"     },
        { TOK_ELSE,         "else"  },
        { TOK_LBRACE,       "{"     },
        { TOK_RETURN,       "return"},
        { TOK_FALSE,        "false" },
        { TOK_SEMICOLON,    ";"     },
        { TOK_RBRACE,       "}"     },
        { TOK_INT,          "10"    },
        { TOK_EQ,           "=="    },
        { TOK_INT,          "10"    },
        { TOK_SEMICOLON,    ";"     },
        { TOK_INT,          "10"    },
        { TOK_NOT_EQ,       "!="    },
        { TOK_INT,          "9"     },
        { TOK_SEMICOLON,    ";"     },
        { TOK_EOF,          ""      },
        { -1,               NULL    },
    });

    return EXIT_SUCCESS;
}

