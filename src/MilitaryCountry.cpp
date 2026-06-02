#include "MilitaryCountry.hpp"

MilitaryCountry::MilitaryCountry(std::string n,
                                 const std::vector<Country*>& neigh,
                                 Player* own,
                                 int prodIndex,
                                 int tier,
                                 float defense,
                                 int garrison)
    : Country(std::move(n), neigh, own, prodIndex, tier),
      defenseBonus(defense),
      garrisonSize(garrison) {}

MilitaryCountry::MilitaryCountry(const MilitaryCountry& other)
    : Country(other),
      defenseBonus(other.defenseBonus),
      garrisonSize(other.garrisonSize) {
    std::cout << "[MilitaryCountry] Copy constructor pentru "
              << getName() << '\n';
}

MilitaryCountry& MilitaryCountry::operator=(const MilitaryCountry& other) {
    if (this != &other) {
        Country::operator=(other);
        defenseBonus = other.defenseBonus;
        garrisonSize = other.garrisonSize;
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
    // (armata functioneaza si in haos, dar mai putin eficient)
    float base             = static_cast<float>(baseProduction());
    float stabilityInfluence = 0.5f + 0.5f * stabilityFactor;
    return static_cast<int>(base * stabilityInfluence);
}

int MilitaryCountry::costToBuy() const {
    static constexpr int costs[] = {700, 3000, 12000, 60000, 250000};
    int idx = getTier() - 1;
    if (idx < 0) idx = 0;
    if (idx > 4) idx = 4;
    return static_cast<int>(static_cast<float>(costs[idx]) * defenseBonus);
}

float MilitaryCountry::stabilityBonus() const {
    // Fiecare unitate de garnizaona ofera un mic bonus de stabilitate pasiv
    // Folosit in GameScreen::update() pentru a compensa scaderea stabilitatii
    return 0.05f * static_cast<float>(garrisonSize);
}

std::string MilitaryCountry::getTypeName() const {
    return "Military";
}

void MilitaryCountry::displayInfo(std::ostream& os) const {
    os << "MilitaryCountry[" << getName() << "]"
       << " tier="          << getTier()
       << " garrison="      << getGarrisonSize()
       << " defenseBonus="  << getDefenseBonus()
       << " stabilityBonus=" << stabilityBonus()
       << " income(stab=1.0)=" << produceIncome(1.0f)
       << " cost="          << costToBuy()
       << " owner="         << (getOwner() ? "Player" : "None");
}

float MilitaryCountry::getDefenseBonus() const { return defenseBonus; }
int   MilitaryCountry::getGarrisonSize() const { return garrisonSize; }