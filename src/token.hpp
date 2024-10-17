#pragma once

namespace token {

enum TokenType {
    PLUS = 0,
    MINUS,
    STAR,
    SLASH,
    INTLIT,
    SEMI,
    PRINT,
    ASSIGN,
    IDENT,
    INT,
    EoF,
    INVALID
};

struct Token {
    TokenType token;
    int intValue;
};

} // End of namespace token
