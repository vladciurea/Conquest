#include "AgriculturalCountry.hpp"

AgriculturalCountry::AgriculturalCountry(std::string n,
                                         const std::vector<Country*>& neigh,
                                         Player* own,
                                         int prodIndex,
                                         int tier,
                                         float bonus)
    : Country(std::move(n), neigh, own, prodIndex, tier),
      fertileBonus(bonus) {}

AgriculturalCountry::AgriculturalCountry(const AgriculturalCountry& other)
    : Country(other), fertileBonus(other.fertileBonus) {
    std::cout << "[AgriculturalCountry] Copy constructor pentru "
              << getName() << '\n';
}

AgriculturalCountry& AgriculturalCountry::operator=(const AgriculturalCountry& other) {
    if (this != &other) {
        Country::operator=(other);
        fertileBonus = other.fertileBonus;
    }
    std::cout << "[AgriculturalCountry] operator= pentru " << getName() << '\n';
    return *this;
}

AgriculturalCountry::~AgriculturalCountry() {
    std::cout << "[AgriculturalCountry] Destructor pentru " << getName() << '\n';
}

AgriculturalCountry* AgriculturalCountry::clone() const {
    return new AgriculturalCountry(*this);
}

int AgriculturalCountry::produceIncome(float /*stabilityFactor*/) const {
    // Taranii muncesc indiferent de stabilitate - ignoram stabilityFactor
    // dar aplicam bonusul de fertilitate
    return static_cast<int>(static_cast<float>(baseProduction()) * fertileBonus);
}

int AgriculturalCountry::costToBuy() const {
    static constexpr int costs[] = {150, 700, 12000, 60000, 250000};
    int idx = getTier() - 1;
    if (idx < 0) idx = 0;
    if (idx > 4) idx = 4;
    return costs[idx];
}

std::string AgriculturalCountry::getTypeName() const {
    return "Agricultural";
}

void AgriculturalCountry::displayInfo(std::ostream& os) const {
    os << "AgriculturalCountry[" << getName() << "]"
       << " tier=" << getTier()
       << " fertileBonus=" << getFertileBonus()
       << " income=" << produceIncome(1.0f)
       << " cost=" << costToBuy()
       << " owner=" << (getOwner() ? "Player" : "None");
}


float AgriculturalCountry::getFertileBonus() const {
    return fertileBonus;
}