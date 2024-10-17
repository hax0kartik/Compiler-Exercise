#include <iostream>
#include "interpret.hpp"
#include "ast.hpp"

static const char *ASTop[] { "+", "-", "*", "/" };

int interpret::interpret_ast(ast::ASTnode *t) {
    int leftVal {0}, rightVal {0};
    
    if (t->left != nullptr)
        leftVal = interpret_ast(t->left);

    if (t->right != nullptr)
        rightVal = interpret_ast(t->right);

    if (t->op == ast::NodeType::INTLIT)
        std::cout << "int " << t->v.intVal << "\n";
    else
        std::cout << leftVal << " " << ASTop[t->op] << " " << rightVal << "\n";

    switch (t->op) {
        case ast::NodeType::ADD:
            return leftVal + rightVal;
        
        case ast::NodeType::SUBTRACT:
            return leftVal - rightVal;
        
        case ast::NodeType::MULTIPLY:
            return leftVal * rightVal;
        
        case ast::NodeType::DIVIDE:
            return leftVal / rightVal;
        
        case ast::NodeType::INTLIT:
            return t->v.intVal;
        
        default:
            std::cerr << "Unknown NodeType: " << t->op << "\n";
            exit(1);
    }
}