#pragma once

#include "Ability.hpp"

#include <iostream>
#include <vector>


class Country;

class Player {
    std::vector<Country*> ownedCountries;
    int                   goldAmount = 0;
    float                 stability  = 100.0f;
    std::vector<Ability>  abilities;

public:
    Player(const std::vector<Country*>& owned,
           int gold,
           float stab,
           const std::vector<Ability>& abil);

    [[nodiscard]] int   getGold()       const;
    [[nodiscard]] float getStability()  const;
    [[nodiscard]] int   getOwnedCount() const;

    // Expune referinta la gold pentru Advisor (hire/salary)
    int& goldRef();

    [[nodiscard]] int calculateTotalIncome() const;
    void collectIncome();

    bool buyCountry(Country& target);
    void giveSpeech(int choice);
    bool useAbility(size_t idx);
    void listAbilities() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
};