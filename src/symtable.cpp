#include <cstring>
#include <iostream>
#include "symtable.hpp"


static void print_symtable(SymTable *table) {
    std::cout << "Number of entries in the table: " << table->counter << "\n";

    for (int i = 0; i < table->counter; i++) {
        std::cout << i << ". Entry: " << table->symbols[i].sym << "\n"; 
    }
}

int SymTable::find_sym(const char *sym) {
    // print_symtable(this);

    for (int i = 0; i <= counter; i++) {
        if (strcmp(sym, symbols[i].sym) == 0) {
            return i;
        }
    }

    return -1;
}


int SymTable::add_sym(const char *sym) {   
    int y = find_sym(sym);

    if (y != -1)
        return y;

    if (counter + 1 >= MAX_SYMBOLS) {
        std::cerr << "Max symbols reached\n";
        exit(1);
    }

    symbols[++counter].sym = strdup(sym);
    return counter;
}
