#include "IndustrialCountry.hpp"

IndustrialCountry::IndustrialCountry(std::string n,
                                     const std::vector<Country*>& neigh,
                                     bool isOwnedInit,
                                     int prodIndex,
                                     int tier,
                                     float pollution,
                                     int factories)
    : Country(std::move(n), neigh, isOwnedInit, prodIndex, tier),
      pollutionRate(pollution), factoryLevel(factories) {}

IndustrialCountry::IndustrialCountry(const IndustrialCountry& other)
    : Country(other),
      pollutionRate(other.pollutionRate),
      factoryLevel(other.factoryLevel) {
    std::cout << "[IndustrialCountry] Copy constructor pentru "
              << getName() << '\n';
}

IndustrialCountry& IndustrialCountry::operator=(const IndustrialCountry& other) {
    if (this != &other) {
        Country::operator=(other);
        pollutionRate = other.pollutionRate;
        factoryLevel  = other.factoryLevel;
    }
    std::cout << "[IndustrialCountry] operator= pentru " << getName() << '\n';
    return *this;
}

IndustrialCountry::~IndustrialCountry() {
    std::cout << "[IndustrialCountry] Destructor pentru " << getName() << '\n';
}

IndustrialCountry* IndustrialCountry::clone() const {
    return new IndustrialCountry(*this);
}

int IndustrialCountry::produceIncome(float stabilityFactor) const {
    // Productia e amplificata de nivelul fabricilor
    // dar penalizata de instabilitate (muncitorii fac greva)
    float base = static_cast<float>(baseProduction() * factoryLevel);
    return static_cast<int>(base * stabilityFactor);
}

int IndustrialCountry::costToBuy() const {
    static constexpr int costs[] = {700, 3000, 12000, 60000, 250000};
    int idx = getTier() - 1;
    if (idx < 0) idx = 0;
    if (idx > 4) idx = 4;
    return costs[idx];
}

std::string IndustrialCountry::getTypeName() const {
    return "Industrial";
}

void IndustrialCountry::displayInfo(std::ostream& os) const {
    os << "IndustrialCountry[" << getName() << "]"
       << " tier=" << getTier()
       << " factories=" << getFactoryLevel()
       << " pollution=" << getPollutionRate()
       << " income(stab=1.0)=" << produceIncome(1.0f)
       << " cost=" << costToBuy()
       << " owned=" << (isOwned() ? "yes" : "no");
}

float IndustrialCountry::getPollutionRate() const {
    return pollutionRate;
}


int IndustrialCountry::getFactoryLevel() const {
    return factoryLevel;
}