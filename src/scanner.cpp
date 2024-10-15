#include <cctype>
#include <cstdio>
#include <cstring>
#include "scanner.hpp"
#include "token.hpp"

static int chrpos(const char *str, char c) {
    const char *p = strchr(str, c);
    return p ? p - str : -1;
}

int Scanner::next() {
    if (putback) {
        char c = putback;
        putback = '\0';
        return c;
    }

    char c = fgetc(f);
    if (c == '\n')
        line++;

    return c;
}

char Scanner::skip() {
    char c = next();

    for (; ; c = next()) {
        if (c != ' ' && c != '\n' && c != '\r' && c != '\t' && c != '\f')
            break;
    }

    return c;
}

int Scanner::scan_int(char c) {
    int k = 0, val = 0;
    
    while ((k = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }

    putback = c;
    return val;
}

int Scanner::scan(token::token *t) {
    /* skip to the very first valid token */
    char c = skip();

    switch (c) {
        case '+':
            t->token = token::TokenType::PLUS;
            break;
        
        case '-':
            t->token = token::TokenType::MINUS;
            break;

        case '*':
            t->token = token::TokenType::STAR;
            break;
        
        case '/':
            t->token = token::TokenType::SLASH;
            break;

        case EOF:
            return 0;

        default:
            if (isdigit(c)) {
                t->intValue = scan_int(c);
                t->token = token::TokenType::INTLIT;
            } else {
                printf("Unknown token: %c ", c);
            }
    }

    return 1;
}
