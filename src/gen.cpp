#include <iostream>
#include "gen.hpp"
#include "ast.hpp"

int Gen::gen_ast(ast::ASTnode *ast) {
    int leftReg {0}, rightReg {0};

    if (ast->left)
        leftReg = gen_ast(ast->left);
    if (ast->right)
        rightReg = gen_ast(ast->right);

    switch(ast->op) {
        case ast::NodeType::ADD:
            return cg->add(leftReg, rightReg);
        
        case ast::NodeType::SUBTRACT:
            return cg->sub(leftReg, rightReg);
        
        case ast::NodeType::MULTIPLY:
            return cg->mul(leftReg, rightReg);
        
        case ast::NodeType::DIVIDE:
            return cg->div(leftReg, rightReg);
        
        case ast::NodeType::INTLIT:
            return cg->load_value(ast->intVal);
        
        default:
            std::cerr << "Unknown AST operator\n" << ast->op;
            exit(1);
    }
}

void Gen::gen_code(ast::ASTnode *ast) {
    int reg {};

    cg->preamble();
    reg = gen_ast(ast);
    cg->print_int(reg);
    cg->postamble();
}