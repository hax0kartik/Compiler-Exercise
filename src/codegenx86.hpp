#pragma once
#include "gen.hpp"
#include "symtable.hpp"
#include <cstdio>

struct CodeGen : Gen {

    CodeGen(FILE *f, SymTable *sym) : Gen(f, sym) {

    }

    void preamble() override;
    void postamble() override;

    int load_value(int value) override;
    int add(int r1, int r2) override;
    int sub(int r1, int r2) override;
    int mul(int r1, int r2) override;
    int div(int r1, int r2) override;

    int store_global(int r, const char *iden) override;
    int load_global(const char *iden) override;
    void gen_global(const char *iden) override;

    void print_int(int r) override;
    void free_registers() override;

    void free_register(int r);
    int alloc_register();

    int freeRegs[4] {};
};
