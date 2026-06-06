#pragma once

#include "Resourcechest.hpp"

class GoldChest : public ResourceChest {
    float goldReward;

public:
    GoldChest(std::string q, const std::vector<std::string>& opts, int correct, float reward);

    GoldChest(const GoldChest& other);
    GoldChest& operator=(const GoldChest& other);
    ~GoldChest() override;

    [[nodiscard]] GoldChest* clone() const override;

    void applyReward(float& gold, float& stability) const override;

    [[nodiscard]] std::string getTypeName() const override;
    [[nodiscard]] std::string getRewardDescription() const override;
    // [[nodiscard]] float getGoldReward() const;

protected:
    void displayInfo(std::ostream& os) const override;
};