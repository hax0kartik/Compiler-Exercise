#include <iostream>
#include <cstdio>
#include "ast.hpp"
#include "expr.hpp"
#include "interpret.hpp"
#include "scanner.hpp"
#include "token.hpp"

void scan_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        std::cout << "Filename not valid?\n";
        return;
    }

    Scanner sc(f);

    ExprParser ep(&sc);
    ast::ASTnode *ast = ep.bin_expr();
    int res = interpret::interpret_ast(ast);
    std::cout << "Final result: " << res << "\n";
}

int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cout << "Please provide filename of the file to scan\n";
        return -1;
    }

    scan_file(argv[1]);

    return 0;
}
