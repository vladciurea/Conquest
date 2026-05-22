#include "Advisor.hpp"
#include "Ability.hpp"
#include "Country.hpp"
#include "Player.hpp"
#include "ResourceChest.hpp"

#include <iostream>
#include <limits>
#include <vector>

int main() {
    Country rom("Romania", {}, nullptr, 3, 2);
    Country bul("Bulgaria", {}, nullptr, 2, 1);
    Country hun("Ungaria", {}, nullptr, 4, 3);
    Country gre("Grecia", {}, nullptr, 1, 1);

    int nr;
    std::cout << "Alege numarul de runde: ";
    std::cin >> nr;

    int runda = 1;
    while (nr) {
        std::cout << "\n===============  Runda " << runda << "  ===============\n";
        runda++;

        rom = Country("Romania",  {&bul, &hun}, nullptr, 3, 2);
        bul = Country("Bulgaria", {&rom, &gre}, nullptr, 2, 1);
        hun = Country("Hungary",  {&rom},       nullptr, 4, 3);
        gre = Country("Greece",   {&bul},       nullptr, 1, 1);

        std::vector<Ability> abil = {
            Ability("PeoplePleaser", "Scade pierderea stabilitatii temporar", 80, +8, true),
            Ability("MilitaryPower", "Reduce costurile de cumparare", 60, +3, true)
        };

        Player player({}, 500, 90.0f, abil);

        Advisor econAdvisor("Mihai Viteazul", "Economic", 100, 20);
        Advisor milAdvisor("Stefan cel Mare", "Military", 150, 30);

        std::cout << "Start game:\n" << player << "\n";
        std::cout << "--- Advisori disponibili:\n"
                  << econAdvisor << "\n" << milAdvisor << "\n";
        std::cout << "--- Harta (tari):\n"
                  << rom << "\n" << bul << "\n" << hun << "\n" << gre << "\n";

        std::cout << "\n--- Angajare advisor economic la start ---\n";
        econAdvisor.hire(player.goldRef());
        std::cout << econAdvisor << "\n";

        for (int turn = 1; turn <= 3; ++turn) {
            std::cout << "\n====== Turn " << turn << " ======\n";

            player.collectIncome();
            econAdvisor.paySalary(player.goldRef());
            milAdvisor.paySalary(player.goldRef());

            int advisorRec = -1;
            if (econAdvisor.isActive()) {
                advisorRec = econAdvisor.recommend(
                    player.getGold(), player.getStability(), player.getOwnedCount());
            } else if (milAdvisor.isActive()) {
                advisorRec = milAdvisor.recommend(
                    player.getGold(), player.getStability(), player.getOwnedCount());
            }

            std::cout << "Actiuni disponibile:\n"
                      << "  1) Cumpara o tara\n"
                      << "  2) Cucereste o tara (daca e vecina)\n"
                      << "  3) Deschide un ResourceChest (quiz)\n"
                      << "  4) Tine un discurs (alegere 1..3)\n"
                      << "  5) Foloseste o abilitate\n"
                      << "  6) Angajeaza advisorul militar\n"
                      << "  0) Skip\n"
                      << "Alege actiunea (numar): ";

            int action = -1;
            if (!(std::cin >> action)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                action = 0;
            }

            if (advisorRec != -1) {
                bool followed = (action == advisorRec);
                if (econAdvisor.isActive())      econAdvisor.reportFollowed(followed);
                else if (milAdvisor.isActive())  milAdvisor.reportFollowed(followed);
            }

            Country* target = nullptr;
            if (action == 1 || action == 2) {
                std::cout << "Ce tara? (1 Romania, 2 Bulgaria, 3 Hungary/Ungaria, 4 Greece/Grecia): ";
                int c = 0;
                if (!(std::cin >> c)) { std::cin.clear(); std::cin.ignore(); }
                if (c == 1) target = &rom;
                else if (c == 2) target = &bul;
                else if (c == 3) target = &hun;
                else if (c == 4) target = &gre;
            }

            if      (action == 1 && target) player.buyCountry(*target);
            else if (action == 2 && target) player.conquer(*target);
            else if (action == 3) {
                ResourceChest rc("Care este capitala Romaniei?",
                                 {"Sofia", "Bucuresti", "Budapesta"},
                                 1, 150, 3);
                rc.presentAndResolve();
            }
            else if (action == 4) {
                std::cout << "Alege tip discurs: 1=bold, 2=calm, 3=medium: ";
                int ch = 0;
                if (!(std::cin >> ch)) { std::cin.clear(); std::cin.ignore(); }
                player.giveSpeech(ch);
            }
            else if (action == 5) {
                player.listAbilities();
                std::cout << "Alege index abilitate: ";
                size_t idx = 0;
                if (!(std::cin >> idx)) {
                    std::cin.clear(); std::cin.ignore();
                    idx = std::numeric_limits<size_t>::max();
                }
                if (idx != std::numeric_limits<size_t>::max()) player.useAbility(idx);
            }
            else if (action == 6) {
                if (!milAdvisor.isActive()) milAdvisor.hire(player.goldRef());
                else std::cout << "Advisorul militar este deja activ.\n";
            }
            else if (action != 0) {
                std::cout << "Skip action.\n";
            }

            std::cout << "--- Stare advisori:\n"
                      << "  " << econAdvisor << "\n"
                      << "  " << milAdvisor  << "\n";
            std::cout << "Sfarsit turn " << turn << ". " << player << "\n";
        }

        std::cout << "\nFinal game state:\n" << player << "\n";
        std::cout << "Harta finala:\n"
                  << rom << "\n" << bul << "\n" << hun << "\n" << gre << "\n";
        nr--;
    }
    return 0;
}