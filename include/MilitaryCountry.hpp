#pragma once

#include "Country.hpp"

// Tara militara: venit mediu, dar face tara mai scumpa de cumparat
// (defenseBonus) si ofera un bonus de stabilitate imperiului
// (prezenta militara tine ordinea).
// Caracteristica speciala: defenseBonus si garrisonSize.
class MilitaryCountry : public Country {
    float defenseBonus;  // multiplica costul de cumparare al acestei tari
    int   garrisonSize;  // marimea garnizoanei, amplifica defenseBonus
    // si ofera bonus de stabilitate pasiv

public:
    MilitaryCountry(std::string n,
                    const std::vector<Country*>& neigh,
                    bool isOwnedInit,
                    int prodIndex,
                    int tier,
                    float defense = 1.2f,
                    int garrison  = 1);

    MilitaryCountry(const MilitaryCountry& other);
    MilitaryCountry& operator=(const MilitaryCountry& other);
    ~MilitaryCountry() override;

    [[nodiscard]] MilitaryCountry* clone() const override;

    // Specific temei: venitul e moderat, afectat partial de stabilitate
    [[nodiscard]] int produceIncome(float stabilityFactor) const override;

    // Cea mai scumpa categorie - defenseBonus o face si mai scumpa
    [[nodiscard]] int costToBuy() const override;

    // bonus de stabilitate pasiv oferit imperiului
    // (returneaza cat creste stabilitatea pe tick cat timp e detinuta)
    [[nodiscard]] float stabilityBonus() const;

    [[nodiscard]] std::string getTypeName() const override;

    void displayInfo(std::ostream& os) const override;

    [[nodiscard]] float getDefenseBonus() const;
    [[nodiscard]] int   getGarrisonSize() const;

    // Mareste garnizaona - creste defenseBonus si stabilityBonus
};