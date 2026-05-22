#include "Advisor.hpp"

Advisor::Advisor(std::string n, std::string spec, int hire, int salary)
    : name(std::move(n)), specialty(std::move(spec)),
      hireCost(hire), salaryCostPerTurn(salary) {}

Advisor::Advisor(const Advisor& other)
    : name(other.name), specialty(other.specialty),
      hireCost(other.hireCost), salaryCostPerTurn(other.salaryCostPerTurn),
      loyalty(other.loyalty), active(other.active),
      lastRecommendedAction(other.lastRecommendedAction) {
    std::cout << "[Advisor] Copy constructor pentru " << name << '\n';
}

Advisor& Advisor::operator=(const Advisor& other) {
    if (this != &other) {
        name                  = other.name;
        specialty             = other.specialty;
        hireCost              = other.hireCost;
        salaryCostPerTurn     = other.salaryCostPerTurn;
        loyalty               = other.loyalty;
        active                = other.active;
        lastRecommendedAction = other.lastRecommendedAction;
    }
    std::cout << "[Advisor] operator= pentru " << name << '\n';
    return *this;
}

Advisor::~Advisor() {
    std::cout << "[Advisor] Destructor pentru " << name << '\n';
}

const std::string& Advisor::getName()  const { return name; }
bool               Advisor::isActive() const { return active; }

bool Advisor::hire(int& playerGold) {
    if (active) {
        std::cout << "[Advisor] " << name << " este deja angajat.\n";
        return false;
    }
    if (playerGold < hireCost) {
        std::cout << "[Advisor] Nu ai destul aur pentru a angaja " << name
                  << " (cost=" << hireCost << ", ai=" << playerGold << ")\n";
        return false;
    }
    playerGold -= hireCost;
    active  = true;
    loyalty = 80.0f;
    std::cout << "[Advisor] " << name << " (" << specialty
              << ") a fost angajat pentru " << hireCost << " aur.\n";
    return true;
}

void Advisor::paySalary(int& playerGold) {
    if (!active) return;
    if (playerGold >= salaryCostPerTurn) {
        playerGold -= salaryCostPerTurn;
        std::cout << "[Advisor] Salariu platit lui " << name
                  << " (" << salaryCostPerTurn << " aur).\n";
    } else {
        loyalty -= 15.0f;
        std::cout << "[Advisor] Nu ai putut plati salariul lui " << name
                  << "! Loialitate -15 (acum: " << loyalty << ")\n";
        if (loyalty <= 0.0f) {
            loyalty = 0.0f;
            active  = false;
            std::cout << "[Advisor] " << name << " a demisionat!\n";
        }
    }
}

int Advisor::recommend(int gold, float stability, int ownedCountries) {
    if (!active) return -1;

    int rec = 0;
    if (specialty == "Economic") {
        if (gold < 100)          rec = 3;
        else if (stability < 40.0f) rec = 4;
        else                     rec = 1;
    } else if (specialty == "Military") {
        if (stability > 60.0f && gold > 200) rec = 2;
        else if (stability < 50.0f)          rec = 4;
        else                                 rec = 5;
    } else {
        if (ownedCountries == 0)    rec = 1;
        else if (stability < 55.0f) rec = 4;
        else                        rec = 1;
    }

    lastRecommendedAction = rec;

    std::cout << "[Advisor] " << name << " recomanda actiunea " << rec;
    if      (loyalty >= 70.0f) std::cout << " (sfat de incredere - loialitate ridicata)";
    else if (loyalty >= 40.0f) std::cout << " (sfat rezonabil)";
    else                       std::cout << " (sfat incert - loialitate scazuta, ia-l cu rezerve)";
    std::cout << "\n";

    return rec;
}

void Advisor::reportFollowed(bool followed) {
    if (!active || lastRecommendedAction == -1) return;
    if (followed) {
        loyalty += 5.0f;
        if (loyalty > 100.0f) loyalty = 100.0f;
        std::cout << "[Advisor] " << name
                  << " este multumit ca i-ai urmat sfatul. Loialitate +5 ("
                  << loyalty << ")\n";
    } else {
        loyalty -= 8.0f;
        if (loyalty < 0.0f) {
            loyalty = 0.0f;
            active  = false;
            std::cout << "[Advisor] " << name
                      << " a demisionat din cauza ca ii ignori constant sfaturile!\n";
        } else {
            std::cout << "[Advisor] " << name << " este dezamagit. Loialitate -8 ("
                      << loyalty << ")\n";
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Advisor& a) {
    os << "Advisor[" << a.name << " | " << a.specialty
       << " | loialitate=" << a.loyalty
       << " | salariu/turn=" << a.salaryCostPerTurn
       << " | " << (a.active ? "ACTIV" : "INACTIV") << "]";
    return os;
}