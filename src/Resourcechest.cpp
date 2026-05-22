#include "ResourceChest.hpp"

#include <limits>

ResourceChest::ResourceChest(std::string q,
                             const std::vector<std::string>& opts,
                             int correct,
                             int reward,
                             int life)
    : question(std::move(q)), options(opts), correctIndex(correct),
      rewardGold(reward), lifeTimeTurns(life) {}

int ResourceChest::presentAndResolve() const {
    std::cout << "---- Resource Chest ----\n";
    std::cout << question << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "  " << (i + 1) << ") " << options[i] << "\n";
    }
    std::cout << "Alege optiunea (numar): ";

    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input invalid. Nu primesti aur.\n";
        return 0;
    }
    if (choice - 1 == correctIndex) {
        std::cout << "Raspuns corect! Primesti " << rewardGold << " aur.\n";
        return rewardGold;
    }
    std::cout << "Raspuns gresit. Nicio recompensa.\n";
    return 0;
}

std::ostream& operator<<(std::ostream& os, const ResourceChest& rc) {
    os << "ResourceChest[q=\"" << rc.question << "\" reward=" << rc.rewardGold
       << " life=" << rc.lifeTimeTurns << "]";
    return os;
}