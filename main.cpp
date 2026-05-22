#include "game.hpp"

#include <iostream>
#include <stdexcept>

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Eroare fatala: " << e.what() << "\n";
        return 1;
    }
    return 0;
}