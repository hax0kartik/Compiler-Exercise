#include <cstdio>
#include <iostream>
#include "codegenx86.hpp"

static const char *reglist[] {"%r8", "%r9", "%r10", "%r11"};

void CodeGen::free_registers() {
    freeRegs[0] = freeRegs[1] = freeRegs[2] = freeRegs[3] = 1;
}

void CodeGen::free_register(int r) {
    if (freeRegs[r] != 0) {
        std::cerr << "Trying to free a freed register " << r << "\n";
        exit(1);
    }

    freeRegs[r] = 1;
}

int CodeGen::alloc_register() {
    for (int i = 0; i < 4; i++) {
        if (freeRegs[i]) {
            freeRegs[i] = 0;
            return i;
        }
    }

    std::cerr << "Out of free registers\n";
    exit(1);
}

void CodeGen::preamble() {
    free_registers();

    fputs(
        "\t.text\n"
        ".LC0:\n"
        "\t.string\t\"%d\\n\"\n"
        "print_int:\n"
        "\tpushq\t%rbp\n"
        "\tmovq\t%rsp, %rbp\n"
        "\tsubq\t$16, %rsp\n"
        "\tmovl\t%edi, -4(%rbp)\n"
        "\tmovl\t-4(%rbp), %eax\n"
        "\tmovl\t%eax, %esi\n"
        "\tleaq	.LC0(%rip), %rdi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	printf@PLT\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "\t.globl\tmain\n"
        "\t.type\tmain, @function\n"
        "main:\n"
        "\tpushq\t%rbp\n"
        "\tmovq	%rsp, %rbp\n"
        ,outfile
    );

}

void CodeGen::postamble() {
    fputs(
    "\tmovl $0, %eax\n"
    "\tpopq %rbp\n"
    "\tret\n"
    ,outfile);
}

int CodeGen::load_value(int value) {
    int r = alloc_register();

    fprintf(outfile, "\tmovq\t$%d, %s\n", value, reglist[r]);
    return r;
}

int CodeGen::add(int r1, int r2) {
    fprintf(outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);

    return r2;
} 

int CodeGen::sub(int r1, int r2) {
    fprintf(outfile, "\tsubq\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r2);

    return r1;
}

int CodeGen::mul(int r1, int r2) {
    fprintf(outfile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);

    return r2;
}

int CodeGen::div(int r1, int r2) {
    fprintf(outfile, "\tmovq\t%s, %%rax\n", reglist[r1]);
    fprintf(outfile, "\tcqo\n");
    fprintf(outfile, "\tidivq\t%s\n", reglist[r2]);
    fprintf(outfile, "\tmovq\t%%rax,%s\n", reglist[r1]);
    free_register(r2);

    return r1;
}

void CodeGen::print_int(int r) {
    fprintf(outfile, "\tmovq\t%s, %%rdi\n", reglist[r]);
    fprintf(outfile, "\tcall\tprint_int\n");
    free_register(r);
}