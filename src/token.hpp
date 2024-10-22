#pragma once

namespace token {

enum TokenType {
    PLUS = 0,
    MINUS,
    STAR,
    SLASH,

    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,

    INTLIT,
    SEMI,
    ASSIGN,
    IDENT,
    
    PRINT,
    INT,

    EoF,
    INVALID
};

struct Token {
    TokenType token;
    int intValue;
};

} // End of namespace token
