#pragma once
#define MAX_SYMBOLS 1024

struct Symbol {
    char *sym;

    Symbol() : sym(nullptr) {
    }
};

struct SymTable {
    Symbol *symbols;
    int counter;

    SymTable() : counter(-1) {
        symbols = new Symbol[MAX_SYMBOLS];
    }

    int find_sym(const char *sym);
    int add_sym(const char *sym);
};
