#include <iostream>
#include "expr.hpp"
#include "ast.hpp"
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
            std::cerr << "Unknown Token type : " << TokenType::INVALID << '\n';
            return NodeType::INVALID;
    }

    return NodeType::INVALID;
}

ASTnode *ExprParser::primary(Token *t) {
    ASTnode *node {nullptr};

    switch (t->token) {
        case TokenType::INTLIT:
            node = ASTnode::mk_ast_leaf(NodeType::INTLIT, t->intValue);
            break;
        
        default:
            std::cerr << "Syntax error on line: " << sc->line << " " << t->token << "\n";
    }

    return node;
}

ASTnode *ExprParser::bin_expr() {
    ASTnode *left {nullptr}, *right {nullptr};
    Token t;

    sc->scan(&t);

    left = primary(&t);

    sc->scan(&t);

    if (t.token == TokenType::EoF) {
        return left;
    }

    NodeType nt {NodeType::INVALID};
    
    nt = arithop(t.token);

    /* recusrively build the right subtree */
    right = bin_expr();

    return ASTnode::mk_ast_node(nt, left, right, 0);
}
