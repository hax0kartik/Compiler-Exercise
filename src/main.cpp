#include <iostream>
#include <cstdio>
#include "ast.hpp"
#include "codegenx86.hpp"
#include "expr.hpp"
#include "gen.hpp"
#include "interpret.hpp"
#include "scanner.hpp"
#include "stmt.hpp"
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
    Gen *cg = new CodeGen(f2);
    StmtParser parser(&sc, cg);

    cg->preamble();
    parser.statements();
    cg->postamble();

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
