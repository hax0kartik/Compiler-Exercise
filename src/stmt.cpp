#include "stmt.hpp"
#include "ast.hpp"
#include "misc.hpp"
#include "token.hpp"

void StmtParser::var_decl(token::Token *t) {
    misc::match(sc, t, token::TokenType::INT, "int");

    sc->scan(t);
    misc::ident(sc, t);

    symtable->add_sym(sc->last_identifier);
    cg->gen_global(sc->last_identifier);

    sc->scan(t);
    misc::semi(sc, t);
}

void StmtParser::assigment_statement(token::Token *t) {
    ast::ASTnode *left, *right, *tree;
    int id{-1};

    misc::ident(sc, t);

    if ((id = symtable->find_sym(sc->last_identifier)) == -1)
        misc::fatals("Undeclared variable", sc->last_identifier, sc->line);

    right = ast::ASTnode::mk_ast_leaf(ast::NodeType::LVIDENT, id);

    sc->scan(t);
    misc::match(sc, t, token::TokenType::ASSIGN, "=");

    left = ep.bin_expr(t);
    tree = ast::ASTnode::mk_ast_node(ast::NodeType::ASSIGN, left, right, 0);

    cg->gen_ast(tree, -1);
    cg->free_registers();

    misc::semi(sc, t);
}

void StmtParser::print_statement(token::Token *t) {
    ast::ASTnode *tree;
    int reg;

    misc::match(sc, t, token::TokenType::PRINT, "print");

    tree = ep.bin_expr(t);
    reg = cg->gen_ast(tree, -1);
    cg->print_int(reg);
    cg->free_registers();
            
    misc::semi(sc, t);
}

void StmtParser::statements() {
    token::Token t;
    while (1) {
        sc->scan(&t);

        switch (t.token) {
            case token::TokenType::PRINT:
                print_statement(&t);
                break;

            case token::TokenType::INT:
                var_decl(&t);
                break;
            
            case token::TokenType::IDENT:
                assigment_statement(&t);
                break;
            
            case token::TokenType::EoF:
                return;

            default:
                misc::fatald("Statement Error: Unexpected token", t.token, sc->line);
        }
    }
}
