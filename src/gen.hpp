#pragma once
#include <cstdio>
#include "ast.hpp"

struct Gen {
    FILE *outfile;

    Gen(FILE *_outfile) : outfile(_outfile) {

    }
    
    int gen_ast(ast::ASTnode *node);
    void gen_code(ast::ASTnode *ast);

    virtual int load_value(int value) = 0;
    virtual int add(int r1, int r2) = 0;
    virtual int sub(int r1, int r2) = 0;
    virtual int mul(int r1, int r2) = 0;
    virtual int div(int r1, int r2) = 0;
    virtual void preamble() = 0;
    virtual void postamble() = 0;
    virtual void free_registers() = 0;
    virtual void print_int(int r) = 0;
};
