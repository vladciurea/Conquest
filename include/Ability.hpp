#pragma once

#include <iostream>
#include <string>

class Ability {
    std::string name;
    std::string description;
    int goldCost = 0;
    int stabilityEffect = 0;
    bool consumable = true;

public:
    Ability(std::string n, std::string d, int cost, int stabEff, bool cons = true);

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getGoldCost() const;
    [[nodiscard]] int getStabilityEffect() const;
    [[nodiscard]] bool isConsumable() const;

    friend std::ostream& operator<<(std::ostream& os, const Ability& a);
};