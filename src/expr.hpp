#pragma once
#include "ast.hpp"
#include "scanner.hpp"
#include "token.hpp"

using namespace ast;

struct ExprParser {
    Scanner *sc;

    ExprParser(Scanner *_sc) : sc(_sc) {
    }

    ASTnode *bin_expr(token::Token *t);

    private:
    ASTnode *primary(token::Token *t);
    ASTnode *multiplicative_expr(token::Token *t);
    ASTnode *additive_expr(token::Token *t);
};
