#pragma once

#include "Country.hpp"

class TechCountry : public Country {
    float innovationFactor;
    int   researchLevel;

public:
    TechCountry(std::string n,
                const std::vector<Country*>& neigh,
                bool isOwnedInit,
                int prodIndex,
                int tier,
                float innovation = 1.5f,
                int research      = 1);

    TechCountry(const TechCountry& other);
    TechCountry& operator=(const TechCountry& other);
    ~TechCountry() override;

    [[nodiscard]] TechCountry* clone() const override;

    [[nodiscard]] int produceIncome(float stabilityFactor) const override;
    [[nodiscard]] int costToBuy() const override;

    [[nodiscard]] std::string getTypeName() const override;
    void displayInfo(std::ostream& os) const override;

    [[nodiscard]] float getInnovationFactor() const;
    [[nodiscard]] int   getResearchLevel() const;
};