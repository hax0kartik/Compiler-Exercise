#pragma once

namespace ast {

enum NodeType {
    ADD = 0,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    INTLIT,
    IDENT,
    LVIDENT,
    ASSIGN,
    INVALID
};

struct ASTnode {
    NodeType op;
    ASTnode *left;
    ASTnode *right;

    union {
        int intVal;
        int id;
    } v;

    ASTnode(NodeType _op, ASTnode *_left, ASTnode *_right, int _intVal) : 
      op(_op), left(_left), right(_right) {
        v.intVal = _intVal;
      }

    static ASTnode *mk_ast_node(NodeType _op, ASTnode *_left, ASTnode *_right, int _intVal) {
        return new ASTnode(_op, _left, _right, _intVal);
    }

    static ASTnode *mk_ast_leaf(NodeType _op, int _intVal) {
        return new ASTnode(_op, nullptr, nullptr, _intVal);
    }

    static ASTnode *mk_ast_unary(NodeType _op, ASTnode *_left, int _intVal) {
        return new ASTnode(_op, _left, nullptr, _intVal);
    }
};

} // End of namespace ast
