#pragma once

#include "Country.hpp"

// Tara agricola: venit stabil, nu e penalizata de instabilitate,
// dar produce mai putin decat tarile industriale sau militare.
// Caracteristica speciala: fertileBonus creste venitul sezonier.
class AgriculturalCountry : public Country {
    float fertileBonus; // multiplicator 1.0 = normal, 1.5 = pamant fertil

public:
    AgriculturalCountry(std::string n,
                        const std::vector<Country*>& neigh,
                        bool isOwnedInit,
                        int prodIndex,
                        int tier,
                        float bonus = 1.0f);

    AgriculturalCountry(const AgriculturalCountry& other);
    AgriculturalCountry& operator=(const AgriculturalCountry& other);
    ~AgriculturalCountry() override;

    [[nodiscard]] AgriculturalCountry* clone() const override;

    [[nodiscard]] int produceIncome(float stabilityFactor) const override;

    [[nodiscard]] int costToBuy() const override;

    [[nodiscard]] std::string getTypeName() const override;

    void displayInfo(std::ostream& os) const override;

    [[nodiscard]] float getFertileBonus() const;
};