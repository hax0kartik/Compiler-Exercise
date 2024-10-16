#pragma once
#include "ast.hpp"
#include "expr.hpp"
#include "gen.hpp"
#include "misc.hpp"
#include "scanner.hpp"
#include "token.hpp"

using namespace ast;

struct StmtParser {
    Scanner *sc;
    Gen *cg;
    ExprParser ep;

    StmtParser(Scanner *_sc, Gen *_cg) : sc(_sc), cg(_cg), ep(_sc) {

    }
    
    void statements() {
        ast::ASTnode *tree;
        int reg;
        token::Token t;

        sc->scan(&t);

        while (1) {
            misc::match(sc, &t, token::TokenType::PRINT, "print");

            tree = ep.bin_expr(&t);
            reg = cg->gen_ast(tree);
            cg->print_int(reg);
            cg->free_registers();
            
            misc::semi(sc, &t);
            
            sc->scan(&t);
            if (t.token == token::TokenType::EoF)
                return;
        }
    }
};
