#pragma once
#include <cstdio>
#include "ast.hpp"
#include "symtable.hpp"

struct Gen {
    FILE *outfile;
    SymTable *symtable;

    Gen(FILE *_outfile, SymTable *_sym) : outfile(_outfile), symtable(_sym) {

    }
    
    int gen_ast(ast::ASTnode *node, int reg);
    void gen_code(ast::ASTnode *ast);

    virtual int store_global(int r, const char *iden) = 0;
    virtual int load_global(const char *iden) = 0;
    virtual void gen_global(const char *iden) = 0;

    virtual int load_value(int value) = 0;
    
    virtual int add(int r1, int r2) = 0;
    virtual int sub(int r1, int r2) = 0;
    virtual int mul(int r1, int r2) = 0;
    virtual int div(int r1, int r2) = 0;

    virtual int eq(int r1, int r2) = 0;
    virtual int ne(int r1, int r2) = 0;
    virtual int lt(int r1, int r2) = 0;
    virtual int gt(int r1, int r2) = 0;
    virtual int le(int r1, int r2) = 0;
    virtual int ge(int r1, int r2) = 0;

    virtual void preamble() = 0;
    virtual void postamble() = 0;
    virtual void free_registers() = 0;
    virtual void print_int(int r) = 0;
};
