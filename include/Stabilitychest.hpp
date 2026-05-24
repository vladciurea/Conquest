#pragma once

#include "Resourcechest.hpp"

class StabilityChest : public ResourceChest {
    float stabilityReward;

public:
    StabilityChest(std::string q, const std::vector<std::string>& opts, int correct, float reward);

    StabilityChest(const StabilityChest& other);
    StabilityChest& operator=(const StabilityChest& other);
    ~StabilityChest() override;

    [[nodiscard]] StabilityChest* clone() const override;

    void applyReward(float& gold, float& stability) const override;

    [[nodiscard]] std::string getTypeName() const override;
    [[nodiscard]] std::string getRewardDescription() const override;
    [[nodiscard]] float getStabilityReward() const;

protected:
    void displayInfo(std::ostream& os) const override;
};