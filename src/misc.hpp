#pragma once
#include <iostream>
#include "scanner.hpp"
#include "token.hpp"

namespace misc {

static void match(Scanner *sc, token::Token *t, token::TokenType expTy, const char *what) {
    if (t->token != expTy) {
        std::cerr << what << " was expected on line " << sc->line << "\n";
        exit(1);
    }
}

static void semi(Scanner *sc, token::Token *t) {
    match(sc, t, token::TokenType::SEMI, ";");
}

} // End of namespace misc