#pragma once
#include <iostream>
#include "scanner.hpp"
#include "token.hpp"

namespace misc {

static void match(Scanner *sc, token::Token *t, token::TokenType expTy, const char *what) {
    if (t->token != expTy) {
        std::cerr << what << " was expected on line " << sc->line <<  "\n";
        exit(1);
    }
}

static void semi(Scanner *sc, token::Token *t) {
    match(sc, t, token::TokenType::SEMI, ";");
}

static void ident(Scanner *sc, token::Token *t) { 
    match(sc, t, token::TokenType::IDENT, "identifier"); 
}

static void fatal(const char *s, int line) {
  std::cerr << s << " on line " << line << "\n"; 
  exit(1);
}

static void fatals(const char *s1, const char *s2, int line) {
  std::cerr << s1 << ":" << s2 << " on line " << line << "\n"; 
  exit(1);
}

static void fatald(const char *s, int d, int line) {
  std::cerr << s << ":" << d << " on line " << line << "\n"; 
  exit(1);
}

static void fatalc(const char *s, int c, int line) {
  std::cerr << s << ":" << c << " on line " << line << "\n"; 
  exit(1);
}

} // End of namespace misc