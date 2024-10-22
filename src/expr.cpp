#include <iostream>
#include "expr.hpp"
#include "ast.hpp"
#include "misc.hpp"
#include "token.hpp"

using namespace ast;
using namespace token;

static NodeType arithop(TokenType t) {
    switch (t) {
        case TokenType::PLUS:
            return NodeType::ADD;
        
        case TokenType::MINUS:
            return NodeType::SUBTRACT;
        
        case TokenType::SLASH:
            return NodeType::DIVIDE;
        
        case TokenType::STAR:
            return NodeType::MULTIPLY;
        
        case TokenType::INTLIT:
            return NodeType::INTLIT;

        default:
            std::cerr << "Unknown Token type : " << t << '\n';
            exit(1);
    }

    return NodeType::INVALID;
}

ASTnode *ExprParser::primary(Token *t) {
    ASTnode *node {nullptr};
    int id {-1};

    switch (t->token) {
        case TokenType::INTLIT:
            node = ASTnode::mk_ast_leaf(NodeType::INTLIT, t->intValue);
            break;

        case TokenType::IDENT:
            id = symtable->find_sym(sc->last_identifier);
            if (id == -1)
                misc::fatals("Unknown variable", sc->last_identifier, sc->line);
            
            node = ASTnode::mk_ast_leaf(NodeType::IDENT, id);
            break;
        
        default:
            std::cerr << "Syntax error on line: " << sc->line << " " << t->token << "\n";
            exit(1);
    }

    return node;
}

static int op_precedence(token::TokenType t) {
    if (t == TokenType::EoF)
        return 0;

    else if (t == TokenType::PLUS || t == TokenType::MINUS)
        return 10;

    else if (t == TokenType::STAR || t == TokenType::SLASH)
        return 20;

    else if (t == TokenType::EQ || t == TokenType::NE)
        return 30;

    else
        return 40;
}

ASTnode *ExprParser::bin_expr(Token *t, int ptp) {
    ASTnode *left {nullptr}, *right {nullptr};

    sc->scan(t);
    left = primary(t);

    sc->scan(t);

    TokenType ty = t->token;
    if (ty == TokenType::SEMI)
        return left;

    while (op_precedence(ty) > ptp) {
        right = bin_expr(t, op_precedence(t->token));

        left = ASTnode::mk_ast_node(arithop(ty), left, right, 0);

        ty = t->token;
        if (t->token == token::TokenType::SEMI)
            return left;
    }

    return left;
}
