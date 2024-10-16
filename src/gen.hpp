#pragma once
#include "ast.hpp"
#include "codegenx86.hpp"

struct Gen {
    CodeGen *cg {};

    Gen(CodeGen *_cg) : cg(_cg) {
        
    }

    int gen_ast(ast::ASTnode *node);
    void gen_code(ast::ASTnode *ast);
};
