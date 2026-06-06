#include "Goldchest.hpp"

GoldChest::GoldChest(std::string q, const std::vector<std::string>& opts, int correct, float reward)
    : ResourceChest(std::move(q), opts, correct), goldReward(reward) {}

GoldChest::GoldChest(const GoldChest& other)
    : ResourceChest(other), goldReward(other.goldReward) {}

GoldChest& GoldChest::operator=(const GoldChest& other) {
    if (this != &other) {
        ResourceChest::operator=(other);
        goldReward = other.goldReward;
    }
    return *this;
}

GoldChest::~GoldChest() = default;

GoldChest* GoldChest::clone() const { return new GoldChest(*this); }

void GoldChest::applyReward(float& gold, float& /*stability*/) const {
    gold += goldReward;
}

std::string GoldChest::getTypeName() const { return "GoldChest"; }

std::string GoldChest::getRewardDescription() const {
    return "+" + std::to_string(static_cast<int>(goldReward)) + " aur";
}

// float GoldChest::getGoldReward() const { return goldReward; }

void GoldChest::displayInfo(std::ostream& os) const {
    os << "GoldChest[\"" << getQuestion() << "\""
       << " reward=" << goldReward << " aur]";
}