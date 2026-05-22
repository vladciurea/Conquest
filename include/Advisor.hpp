#pragma once

#include <iostream>
#include <string>

class Advisor {
    std::string name;
    std::string specialty;
    int hireCost = 0;
    int salaryCostPerTurn = 0;
    float loyalty = 80.0f;
    bool active = false;
    int lastRecommendedAction = -1;

public:
    Advisor(std::string n, std::string spec, int hire, int salary);

    Advisor(const Advisor& other);
    Advisor& operator=(const Advisor& other);
    ~Advisor();

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] bool isActive() const;

    bool hire(int& playerGold);
    void paySalary(int& playerGold);
    int  recommend(int gold, float stability, int ownedCountries);
    void reportFollowed(bool followed);

    friend std::ostream& operator<<(std::ostream& os, const Advisor& a);
};