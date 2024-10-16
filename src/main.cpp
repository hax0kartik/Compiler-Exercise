#include <iostream>
#include <cstdio>
#include "ast.hpp"
#include "codegenx86.hpp"
#include "expr.hpp"
#include "gen.hpp"
#include "interpret.hpp"
#include "scanner.hpp"
#include "token.hpp"

void scan_file(const char *filename, const char *outname) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        std::cout << "Filename not valid?\n";
        return;
    }

    FILE *f2 = fopen(outname, "w+");
    if (!f2) {
        std::cout << "Error occured while opening outfile\n";
        return;
    }

    Scanner sc(f);

    ExprParser ep(&sc);
    ast::ASTnode *ast = ep.bin_expr();
    int res = interpret::interpret_ast(ast);
    std::cout << "Interpreted result: " << res << "\n";
    
    CodeGen codegenx86(f2);
    Gen gen(&codegenx86);
    gen.gen_code(ast);

    fclose(f2);
    fclose(f);
}

int main(int argc, const char **argv) {
    if (argc < 3) {
        std::cout << "Please provide filename of the file to scan and code file to generate\n";
        return -1;
    }

    scan_file(argv[1], argv[2]);

    return 0;
}
