#include "TechCountry.hpp"
#include <cmath>

TechCountry::TechCountry(std::string n,
                         const std::vector<Country*>& neigh,
                         bool isOwnedInit,
                         int prodIndex,
                         int tier,
                         float innovation,
                         int research)
    : Country(std::move(n), neigh, isOwnedInit, prodIndex, tier),
      innovationFactor(innovation), researchLevel(research) {}

TechCountry::TechCountry(const TechCountry& other)
    : Country(other),
      innovationFactor(other.innovationFactor),
      researchLevel(other.researchLevel) {
    std::cout << "[TechCountry] Copy constructor pentru " << getName() << '\n';
}

TechCountry& TechCountry::operator=(const TechCountry& other) {
    if (this != &other) {
        Country::operator=(other);
        innovationFactor = other.innovationFactor;
        researchLevel    = other.researchLevel;
    }
    std::cout << "[TechCountry] operator= pentru " << getName() << '\n';
    return *this;
}

TechCountry::~TechCountry() {
    std::cout << "[TechCountry] Destructor pentru " << getName() << '\n';
}

TechCountry* TechCountry::clone() const {
    return new TechCountry(*this);
}

int TechCountry::produceIncome(float stabilityFactor) const {
    float base = static_cast<float>(baseProduction() * researchLevel);
    float techBonus = innovationFactor * stabilityFactor * stabilityFactor;
    return static_cast<int>(base * techBonus);
}

int TechCountry::costToBuy() const {
    static constexpr int costs[] = {700, 3000, 12000, 60000, 225000};
    int idx = getTier() - 1;
    if (idx < 0) idx = 0;
    if (idx > 4) idx = 4;
    return costs[idx];
}

std::string TechCountry::getTypeName() const {
    return "Tech";
}

void TechCountry::displayInfo(std::ostream& os) const {
    os << "TechCountry[" << getName() << "]"
       << " tier="       << getTier()
       << " research="   << getResearchLevel()
       << " innovation=" << getInnovationFactor()
       << " income(stab=1.0)=" << produceIncome(1.0f)
       << " cost="       << costToBuy()
       << " owned="      << (isOwned() ? "yes" : "no");
}

float TechCountry::getInnovationFactor() const { return innovationFactor; }
int   TechCountry::getResearchLevel()    const { return researchLevel; }