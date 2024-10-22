#include <iostream>
#include "gen.hpp"
#include "ast.hpp"

int Gen::gen_ast(ast::ASTnode *ast, int reg) {
    int leftReg {0}, rightReg {0};

    if (ast->left)
        leftReg = gen_ast(ast->left, -1);
    if (ast->right)
        rightReg = gen_ast(ast->right, leftReg);

    switch(ast->op) {
        case ast::NodeType::ADD:
            return add(leftReg, rightReg);
        
        case ast::NodeType::SUBTRACT:
            return sub(leftReg, rightReg);
        
        case ast::NodeType::MULTIPLY:
            return mul(leftReg, rightReg);
        
        case ast::NodeType::DIVIDE:
            return div(leftReg, rightReg);
        
        case ast::NodeType::INTLIT:
            return load_value(ast->v.intVal);

        case ast::NodeType::IDENT:
            return load_global(symtable->symbols[ast->v.id].sym);

        case ast::NodeType::LVIDENT:
            return store_global(reg, symtable->symbols[ast->v.id].sym);
        
        case ast::NodeType::ASSIGN:
            return rightReg;

        case ast::NodeType::EQ:
            return eq(leftReg, rightReg);

        case ast::NodeType::NE:
            return ne(leftReg, rightReg);

        case ast::NodeType::LT:
            return lt(leftReg, rightReg);
        
        case ast::NodeType::LE:
            return le(leftReg, rightReg);
        
        case ast::NodeType::GT:
            return gt(leftReg, rightReg);

        case ast::NodeType::GE:
            return ge(leftReg, rightReg);
        
        default:
            std::cerr << "Unknown AST operator\n" << ast->op;
            exit(1);
    }
}

void Gen::gen_code(ast::ASTnode *ast) {
    int reg {};

    preamble();
    reg = gen_ast(ast, -1);
    print_int(reg);
    postamble();
}