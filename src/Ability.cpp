#include "Ability.hpp"

Ability::Ability(std::string n, std::string d, int cost, int stabEff, bool cons)
    : name(std::move(n)), description(std::move(d)),
      goldCost(cost), stabilityEffect(stabEff), consumable(cons) {}

const std::string& Ability::getName()            const { return name; }
// cppcheck-suppress unusedFunction
int                Ability::getGoldCost()        const { return goldCost; }
// cppcheck-suppress unusedFunction
int                Ability::getStabilityEffect() const { return stabilityEffect; }
// cppcheck-suppress unusedFunction
bool               Ability::isConsumable()       const { return consumable; }

std::ostream& operator<<(std::ostream& os, const Ability& a) {
    os << "Ability[" << a.name << "] cost=" << a.goldCost
       << " stabEffect=" << a.stabilityEffect
       << " desc=\"" << a.description << "\"";
    return os;
}