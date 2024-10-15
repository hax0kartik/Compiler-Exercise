#include <iostream>
#include <cstdio>
#include "scanner.hpp"
#include "token.hpp"

void scan_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        std::cout << "Filename not valid?\n";
        return;
    }

    Scanner sc(f);

    token::token t;
    const char *t_table[] {"+", "-", "*", "/", "INTLIT"};

    while (sc.scan(&t)) {
        std::cout << "Token: " << t_table[t.token];
        if (t.token == token::TokenType::INTLIT) {
            std::cout << ", Value: " << t.intValue;
        }
        std::cout << "\n";
    }
}

int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cout << "Please provide filename of the file to scan\n";
        return -1;
    }

    scan_file(argv[1]);

    return 0;
}