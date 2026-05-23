#include "Game.hpp"
#include "Gameexceptions.hpp"

#include <iostream>

int main() {
    try {
        Game game;
        game.run();
    }
    catch (const ResourceException& e) {
        std::cerr << "[EROARE RESURSE] " << e.what()
                  << "\n  Deficit: " << e.getDeficit() << " aur\n";
        return 2;
    }
    catch (const CountryException& e) {
        std::cerr << "[EROARE TARA] " << e.what()
                  << "\n  Tara afectata: " << e.getCountryName() << "\n";
        return 3;
    }
    catch (const StabilityException& e) {
        std::cerr << "[EROARE STABILITATE] " << e.what() << "\n";
        if (e.isCollapse())
            std::cerr << "  Imperiul a colapsat! Game over.\n";
        return 4;
    }
    catch (const GameException& e) {
        std::cerr << "[EROARE JOC] " << e.what() << "\n";
        return 5;
    }
    catch (const std::exception& e) {
        std::cerr << "[EROARE SISTEM] " << e.what() << "\n";
        return 1;
    }
    return 0;
}