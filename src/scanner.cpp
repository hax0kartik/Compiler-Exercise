#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "scanner.hpp"
#include "misc.hpp"
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

token::TokenType Scanner::keyword(const char *s) {
    switch (*s) {
        case 'p':
            if (!strcmp(s, "print"))
                return token::TokenType::PRINT;
        case 'i':
            if (!strcmp(s, "int"))
                return token::TokenType::INT;
    }

    return token::TokenType::INVALID;
}

int Scanner::scan_ident(char c, char *buf, int lim) {
    int i = 0;

    while(isalpha(c) || isdigit(c) || '_' == c) {
        if (lim - 1 == i) {
            std::cerr << "Identifier is too long on line" << line << "\n";
            exit(1);
        } else if (i < lim - 1) {
            buf[i++] = c;
        }
        c = next();
    }

    putback = c;
    buf[i] = 0;
    return i;
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

int Scanner::scan(token::Token *t) {
    /* skip to the vnext valid token */
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

        case ';':
            t->token = token::TokenType::SEMI;
            break;
        
        case '=':
            if ((c = next()) == '=')
                t->token = token::TokenType::EQ;
            else { 
                t->token = token::TokenType::ASSIGN;
                putback = c;
            }
            break;
        
        case '!':
            if ((c = next()) == '=') {
                t->token = token::TokenType::NE;
            } else {
                misc::fatalc("Unrecognized character", c, line);
            }
            break;
        
        case '<':
            if ((c = next()) == '=') {
                t->token = token::TokenType::LE;
            } else {
                t->token = token::TokenType::LT;
                putback = c;
            }
            break;

        case '>':
            if ((c = next()) == '=') {
                t->token = token::TokenType::GE;
            } else {
                t->token = token::TokenType::GT;
                putback = c;
            }
            break;

        case EOF:
            t->token = token::TokenType::EoF;
            return 0;

        default:
            if (isdigit(c)) {
                t->intValue = scan_int(c);
                t->token = token::TokenType::INTLIT;
            } else if (isalpha(c) || '_' == c) { // identifiers do not start with a number
                scan_ident(c, last_identifier, MAX_IDENTFIER_LEN);
                token::TokenType ty;
                if ((ty = keyword(last_identifier)) != token::TokenType::INVALID) {
                    t->token = ty;
                    break;
                }

                t->token = token::TokenType::IDENT;
                break;

            } else {
                std::cout << "Unknown token: " << c;
                exit(1);
            }
    }

    return 1;
}
