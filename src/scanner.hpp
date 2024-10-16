#pragma once
#include "token.hpp"
#include <cstdio>

#define MAX_IDENTFIER_LEN 256

struct Scanner {
    int line;
    char putback;
    FILE *f;
    char last_identifier[MAX_IDENTFIER_LEN];

    Scanner(int line_, int putback_, FILE *f_) : line(line_), putback(putback_), f(f_) {

    }

    // We start at line number 1
    Scanner(FILE *f_) : Scanner(1, 0, f_) {

    }

    int scan(token::Token *t);
   
    private:
    int next();
    char skip();
    token::TokenType keyword(const char *s);
    int scan_int(char c);
    int scan_ident(char c, char *buf, int lim);
};
