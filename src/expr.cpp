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

ASTnode *ExprParser::bin_expr(Token *t) {
    return additive_expr(t);
}

ASTnode *ExprParser::multiplicative_expr(Token *t) {
    ASTnode *left {nullptr}, *right {nullptr};

    sc->scan(t);
    
    left = primary(t);

    sc->scan(t);

    if (t->token == TokenType::SEMI) {
        return left;
    }

    TokenType type {t->token};

    while (type == TokenType::SLASH || type == TokenType::STAR) {
        sc->scan(t);

        right = primary(t);

        sc->scan(t);

        left = ASTnode::mk_ast_node(arithop(type), left, right, 0);

        type = t->token;

        if (type == TokenType::SEMI)
            break;
    }

    return left;
}

ASTnode *ExprParser::additive_expr(Token *t) {
    ASTnode *left {nullptr}, *right {nullptr};

    left = multiplicative_expr(t);

    if (t->token == TokenType::SEMI)
        return left;

    TokenType type {t->token};
    
    while (1) {
        right = multiplicative_expr(t);

        left = ASTnode::mk_ast_node(arithop(type), left, right, 0);

        type = t->token;

        if (type == TokenType::SEMI)
            break;
    }

    return left;
}
