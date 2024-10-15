#pragma once

namespace token {

enum TokenType {
    PLUS = 0,
    MINUS,
    STAR,
    SLASH,
    INTLIT
};

struct token {
    int token;
    int intValue;
};

} // End of namespace token
