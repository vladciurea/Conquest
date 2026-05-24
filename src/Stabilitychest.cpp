#include "Stabilitychest.hpp"

StabilityChest::StabilityChest(std::string q, const std::vector<std::string>& opts, int correct, float reward)
    : ResourceChest(std::move(q), opts, correct), stabilityReward(reward) {}

StabilityChest::StabilityChest(const StabilityChest& other)
    : ResourceChest(other), stabilityReward(other.stabilityReward) {}

StabilityChest& StabilityChest::operator=(const StabilityChest& other) {
    if (this != &other) {
        ResourceChest::operator=(other);
        stabilityReward = other.stabilityReward;
    }
    return *this;
}

StabilityChest::~StabilityChest() = default;

StabilityChest* StabilityChest::clone() const { return new StabilityChest(*this); }

void StabilityChest::applyReward(float& /*gold*/, float& stability) const {
    stability += stabilityReward;
    if (stability > 100.f) stability = 100.f;
}

std::string StabilityChest::getTypeName() const { return "StabilityChest"; }

std::string StabilityChest::getRewardDescription() const {
    return "+" + std::to_string(static_cast<int>(stabilityReward)) + "% stabilitate";
}

float StabilityChest::getStabilityReward() const { return stabilityReward; }

void StabilityChest::displayInfo(std::ostream& os) const {
    os << "StabilityChest[\"" << getQuestion() << "\""
       << " reward=" << stabilityReward << "% stabilitate]";
}