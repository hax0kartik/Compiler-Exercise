#pragma once
#include <cstdio>

struct CodeGen {
    FILE *outfile;

    CodeGen(FILE *_outfile) : outfile(_outfile) {
    }

    void preamble();
    void postamble();

    int load_value(int value);
    int add(int r1, int r2);
    int sub(int r1, int r2);
    int mul(int r1, int r2);
    int div(int r1, int r2);

    void print_int(int r);

    private:
    void free_registers();
    void free_register(int r);
    int alloc_register();

    int freeRegs[4] {};
};
