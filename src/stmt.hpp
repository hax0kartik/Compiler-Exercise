#pragma once
#include "ast.hpp"
#include "expr.hpp"
#include "gen.hpp"
#include "misc.hpp"
#include "scanner.hpp"
#include "symtable.hpp"
#include "token.hpp"

using namespace ast;

struct StmtParser {
    Scanner *sc;
    Gen *cg;
    SymTable *symtable;
    ExprParser ep;

    StmtParser(Scanner *_sc, Gen *_cg, SymTable *_sym) : sc(_sc), cg(_cg), symtable(_sym), ep(_sc, _sym) {

    }

    void var_decl(token::Token *t);
    void print_statement(token::Token *t);
    void assigment_statement(token::Token *t);
    void statements();
};
