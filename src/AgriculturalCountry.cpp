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
    // Tarile agricole sunt mai ieftine: baza * 1.5 (fata de 2.0 la altele)
    return 40 * getTier() + static_cast<int>(
        static_cast<float>(baseProduction()) * 1.5f);
}

std::string AgriculturalCountry::getTypeName() const {
    return "Agricultural";
}

void AgriculturalCountry::displayInfo(std::ostream& os) const {
    os << "AgriculturalCountry[" << getName() << "]"
       << " tier=" << getTier()
       << " fertileBonus=" << fertileBonus
       << " income=" << produceIncome(1.0f)
       << " cost=" << costToBuy()
       << " owner=" << (getOwner() ? "Player" : "None");
}

void AgriculturalCountry::setFertileBonus(float bonus) {
    fertileBonus = bonus;
}

float AgriculturalCountry::getFertileBonus() const {
    return fertileBonus;
}