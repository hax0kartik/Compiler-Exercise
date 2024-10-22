#pragma once
#include "ast.hpp"
#include "scanner.hpp"
#include "symtable.hpp"
#include "token.hpp"

using namespace ast;

struct ExprParser {
    Scanner *sc;
    SymTable *symtable;

    ExprParser(Scanner *_sc, SymTable *_sym) 
     : sc(_sc), symtable(_sym) {
    }

    ASTnode *bin_expr(token::Token *t, int ptp = 0);

    private:
    ASTnode *primary(token::Token *t);
};
