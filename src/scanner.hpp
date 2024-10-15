#pragma once
#include "token.hpp"
#include <cstdio>

struct Scanner {
    int line;
    char putback;
    FILE *f;

    Scanner(int line_, int putback_, FILE *f_) : line(line_), putback(putback_), f(f_) {

    }

    // We start at line number 1
    Scanner(FILE *f_) : Scanner(1, 0, f_) {

    }

    int scan(token::token *t);

    private:
    int next();
    char skip();
    int scan_int(char c);
};
