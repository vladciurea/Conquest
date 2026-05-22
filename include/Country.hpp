#pragma once

#include <iostream>
#include <string>
#include <vector>

class Player;

class Country {
    std::string name;
    std::vector<Country*> neighbors;
    int resourceTier = 1;

    Player* owner = nullptr;
    int resourceProdIndex = 1;

public:
    Country(std::string n,
            const std::vector<Country*>& neigh,
            Player* own,
            int prodIndex,
            int tier);

    // Constructorul de copiere si op=
    Country(const Country& other);
    Country& operator=(const Country& other);

    // Destructor VIRTUAL
    virtual ~Country();

    friend std::ostream& operator<<(std::ostream& os, const Country& c);

    [[nodiscard]] virtual int  produceIncome(float stabilityFactor) const = 0;

    [[nodiscard]] virtual int  costToBuy() const = 0;

    // Constructor virtual (clone)
    [[nodiscard]] virtual Country* clone() const = 0;

    // Afisare virtuala - apelata din operator<<
    virtual void displayInfo(std::ostream& os) const = 0;

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getTier() const;
    [[nodiscard]] Player* getOwner() const;
    [[nodiscard]] virtual std::string getTypeName() const = 0;

    void setOwner(Player* p);
    bool isNeighbor(const Country* c) const;

    // Returneaza venitul de baza (fara modificatori specifici tipului)
    // Folosit de derivate ca punct de plecare in produceIncome()
    [[nodiscard]] int baseProduction() const;
};