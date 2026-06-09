#pragma once

#include <iostream>
#include <string>
#include <vector>

class Country {
    std::string           name;
    std::vector<Country*> neighbors;
    int                   resourceTier = 1;

    bool owned             = false;
    int  resourceProdIndex = 1;

public:
    Country(std::string n,
            const std::vector<Country*>& neigh,
            bool isOwnedInit,
            int prodIndex,
            int tier);

    Country(const Country& other);
    Country& operator=(const Country& other);

    virtual ~Country();

    friend std::ostream& operator<<(std::ostream& os, const Country& c);

    [[nodiscard]] virtual int  produceIncome(float stabilityFactor) const = 0;
    [[nodiscard]] virtual int  costToBuy() const = 0;
    [[nodiscard]] virtual Country* clone() const = 0;
    virtual void displayInfo(std::ostream& os) const = 0;

    [[nodiscard]] const std::string& getName()  const;
    [[nodiscard]] int                getTier()   const;
    [[nodiscard]] bool               isOwned()  const;
    [[nodiscard]] virtual std::string getTypeName() const = 0;

    void setOwned(bool value);

    [[nodiscard]] int baseProduction() const;
};