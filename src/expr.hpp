#pragma once
#include <cstdio>
#include "ast.hpp"
#include "scanner.hpp"
#include "token.hpp"

using namespace ast;

struct ExprParser {
    Scanner *sc;

    ExprParser(Scanner *_sc) : sc(_sc) {
    }

    ASTnode *bin_expr();

    private:
    ASTnode *primary(token::Token *t);
};
