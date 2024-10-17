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

    ASTnode *bin_expr(token::Token *t);

    private:
    ASTnode *primary(token::Token *t);
    ASTnode *multiplicative_expr(token::Token *t);
    ASTnode *additive_expr(token::Token *t);
};
