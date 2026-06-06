#include "Player.hpp"
#include "Country.hpp"
#include "Gameexceptions.hpp"

Player::Player(const std::vector<Country*>& owned,
               int gold,
               float stab,
               const std::vector<Ability>& abil)
    : ownedCountries(owned), goldAmount(gold), stability(stab), abilities(abil) {}

// int   Player::getGold()       const { return goldAmount; }
// float Player::getStability()  const { return stability; }
// int   Player::getOwnedCount() const { return static_cast<int>(ownedCountries.size()); }
//
// int& Player::goldRef() { return goldAmount; }

int Player::calculateTotalIncome() const {
    // Calculam stabilityFactor o singura data si il pasam fiecarei tari.
    // Fiecare derivata decide singura cum il foloseste (Agricultural il ignora,
    // Industrial il aplica complet, Military partial).
    float stabilityFactor = stability / 100.0f;
    if (stabilityFactor < 0.0f) stabilityFactor = 0.0f;
    if (stabilityFactor > 1.0f) stabilityFactor = 1.0f;

    int total = 0;
    for (const Country* c : ownedCountries) {
        total += c->produceIncome(stabilityFactor);
    }
    return total;
}

// void Player::collectIncome() {
//     int inc = calculateTotalIncome();
//     goldAmount += inc;
//     std::cout << "Ai colectat " << inc << " aur pasiv (total aur acum: " << goldAmount << ")\n";
// }

// bool Player::buyCountry(Country& target) {
//     if (target.getOwner() == this)
//         throw CountryException(target.getName(), "tara este deja detinuta de acest jucator");
//
//     int cost = target.costToBuy();
//     if (goldAmount < cost)
//         throw ResourceException("cumparare " + target.getName(), goldAmount, cost);
//     if (target.getOwner() != nullptr && target.getOwner() != this) {
//         cost = static_cast<int>(static_cast<float>(cost) * 1.5f);
//         std::cout << "Tara are proprietar, pretul negociat este " << cost << "\n";
//         if (goldAmount < cost) {
//             std::cout << "Nu ai destui bani pentru a negocia cumpararea.\n";
//             return false;
//         }
//     }
//     goldAmount -= cost;
//     if (target.getOwner() != nullptr && target.getOwner() != this) {
//         stability -= 5.0f;
//         std::cout << "Cumparare de la alt proprietar: stabilitatea scade cu 5.\n";
//     } else {
//         stability -= 1.0f;
//     }
//     target.setOwner(this);
//     ownedCountries.push_back(&target);
//     std::cout << "Ai cumparat " << target.getName() << " pentru " << cost << " aur.\n";
//     float extraDecay = 0.5f * static_cast<float>(ownedCountries.size() - 1);
//     stability -= extraDecay;
//     if (stability < 0.0f) stability = 0.0f;
//     return true;
// }



// void Player::giveSpeech(int choice) {
//     std::cout << "Tii un discurs (alegere: " << choice << ")\n";
//     switch (choice) {
//         case 1:
//             stability -= 5.0f;
//             std::cout << "Discurs agresiv: stabilitatea scade cu 5.\n";
//             break;
//         case 2:
//             stability += 7.0f;
//             if (stability > 100.0f) stability = 100.0f;
//             std::cout << "Discurs calm: stabilitatea creste cu 7.\n";
//             break;
//         case 3:
//             stability += 2.0f;
//             if (stability > 100.0f) stability = 100.0f;
//             std::cout << "Discurs echilibrat: stabilitatea creste cu 2.\n";
//             break;
//         default:
//             std::cout << "Alegere invalida. Nimic nu se intampla.\n";
//     }
// }

// bool Player::useAbility(size_t idx) {
//     if (idx >= abilities.size()) {
//         std::cout << "Ability index invalid.\n";
//         return false;
//     }
//     const Ability& ab = abilities[idx];
//     if (goldAmount < ab.getGoldCost()) {
//         std::cout << "Nu ai aur pentru a folosi ability-ul " << ab.getName() << "\n";
//         return false;
//     }
//     goldAmount -= ab.getGoldCost();
//     stability  += static_cast<float>(ab.getStabilityEffect());
//     if (stability > 100.0f) stability = 100.0f;
//     std::cout << "Ai folosit ability-ul " << ab.getName()
//               << ". Stabilitate modificata cu " << ab.getStabilityEffect() << "\n";
//     if (ab.isConsumable()) {
//         abilities.erase(abilities.begin() + static_cast<std::ptrdiff_t>(idx));
//     }
//     return true;
// }

// void Player::listAbilities() const {
//     std::cout << "Abilities (" << abilities.size() << "):\n";
//     for (size_t i = 0; i < abilities.size(); ++i) {
//         std::cout << "  [" << i << "] " << abilities[i] << "\n";
//     }
// }

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "Player gold=" << p.goldAmount
       << " | stability=" << p.stability
       << " | tari detinute=" << p.ownedCountries.size()
       << " | abilitati=" << p.abilities.size()
       << "\n  Tari: [";
    for (size_t i = 0; i < p.ownedCountries.size(); ++i) {
        os << (i ? " | " : "") << *p.ownedCountries[i];
    }
    os << "]";
    return os;
}