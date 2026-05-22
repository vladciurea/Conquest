#pragma once

#include "Country.hpp"

// Tara militara: venit mediu, dar ofera avantaje strategice.
// Reduce costul de cucerire al tarilor vecine si face tara
// mai scumpa de cucerit de adversari (defense bonus).
// Caracteristica speciala: defenseBonus si conquestDiscount.
class MilitaryCountry : public Country {
    float defenseBonus;     // multiplica costul de cucerire al acestei tari (+scump pt adversar)
    float conquestDiscount; // reduce costul de cucerire al vecinilor (0.0 = fara discount)
    int garrisonSize;     // marimea garnizoanei, amplifica defenseBonus

public:
    MilitaryCountry(std::string n,
                    const std::vector<Country*>& neigh,
                    Player* own,
                    int prodIndex,
                    int tier,
                    float defense   = 1.2f,
                    float discount  = 0.1f,
                    int garrison    = 1);

    MilitaryCountry(const MilitaryCountry& other);
    MilitaryCountry& operator=(const MilitaryCountry& other);
    ~MilitaryCountry() override;

    [[nodiscard]] MilitaryCountry* clone() const override;

    // Specific temei: venitul e moderat, afectat partial de stabilitate
    [[nodiscard]] int produceIncome(float stabilityFactor) const override;

    // Cea mai scumpa categorie de tari
    [[nodiscard]] int costToBuy() const override;

    // Specific temei: returneaza costul efectiv de cucerire al unui vecin
    // (aplicand conquestDiscount daca playerul detine aceasta tara)
    [[nodiscard]] int conquerCost(const Country& target) const;

    [[nodiscard]] std::string getTypeName() const override;

    void displayInfo(std::ostream& os) const override;

    [[nodiscard]] float getDefenseBonus() const;
    [[nodiscard]] float getConquestDiscount() const;

    // Mareste garnizaona - creste defenseBonus
    void reinforceGarrison();
    [[nodiscard]] int getGarrisonSize() const;
};