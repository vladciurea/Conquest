#include "MilitaryCountry.hpp"

MilitaryCountry::MilitaryCountry(std::string n,
                                 const std::vector<Country*>& neigh,
                                 Player* own,
                                 int prodIndex,
                                 int tier,
                                 float defense,
                                 float discount,
                                 int garrison)
    : Country(std::move(n), neigh, own, prodIndex, tier),
      defenseBonus(defense),
      conquestDiscount(discount),
      garrisonSize(garrison) {}

MilitaryCountry::MilitaryCountry(const MilitaryCountry& other)
    : Country(other),
      defenseBonus(other.defenseBonus),
      conquestDiscount(other.conquestDiscount),
      garrisonSize(other.garrisonSize) {
    std::cout << "[MilitaryCountry] Copy constructor pentru "
              << getName() << '\n';
}

MilitaryCountry& MilitaryCountry::operator=(const MilitaryCountry& other) {
    if (this != &other) {
        Country::operator=(other);
        defenseBonus     = other.defenseBonus;
        conquestDiscount = other.conquestDiscount;
        garrisonSize     = other.garrisonSize;
    }
    std::cout << "[MilitaryCountry] operator= pentru " << getName() << '\n';
    return *this;
}

MilitaryCountry::~MilitaryCountry() {
    std::cout << "[MilitaryCountry] Destructor pentru " << getName() << '\n';
}

MilitaryCountry* MilitaryCountry::clone() const {
    return new MilitaryCountry(*this);
}

int MilitaryCountry::produceIncome(float stabilityFactor) const {
    // Productia militara e moderata, afectata partial de stabilitate
    // (armata functioneaza si in haos, dar mai greu)
    float base = static_cast<float>(baseProduction());
    float stabilityInfluence = 0.5f + 0.5f * stabilityFactor; // intre 50% si 100%
    return static_cast<int>(base * stabilityInfluence);
}

int MilitaryCountry::costToBuy() const {
    // Cea mai scumpa categorie + defense bonus o face si mai greu de cucerit
    return static_cast<int>(
        static_cast<float>(80 * getTier() + baseProduction() * 2) * defenseBonus);
}

int MilitaryCountry::conquerCost(const Country& target) const {
    // Daca playerul detine aceasta tara militara, vecinii sunt mai usor de cucerit
    int baseCost = static_cast<int>(
        static_cast<float>(target.costToBuy()) * 1.2f);
    float discount = 1.0f - conquestDiscount * static_cast<float>(garrisonSize);
    if (discount < 0.5f) discount = 0.5f; // maxim 50% discount
    return static_cast<int>(static_cast<float>(baseCost) * discount);
}

std::string MilitaryCountry::getTypeName() const {
    return "Military";
}

void MilitaryCountry::displayInfo(std::ostream& os) const {
    os << "MilitaryCountry[" << getName() << "]"
       << " tier=" << getTier()
       << " garrison=" << garrisonSize
       << " defenseBonus=" << defenseBonus
       << " conquestDiscount=" << conquestDiscount
       << " income(stab=1.0)=" << produceIncome(1.0f)
       << " cost=" << costToBuy()
       << " owner=" << (getOwner() ? "Player" : "None");
}

float MilitaryCountry::getDefenseBonus() const { return defenseBonus; }
float MilitaryCountry::getConquestDiscount() const { return conquestDiscount; }

void MilitaryCountry::reinforceGarrison() {
    garrisonSize++;
    defenseBonus += 0.1f;
    std::cout << "[MilitaryCountry] " << getName()
              << " garnizaona intarita la nivel " << garrisonSize
              << " (defenseBonus=" << defenseBonus << ")\n";
}

int MilitaryCountry::getGarrisonSize() const { return garrisonSize; }