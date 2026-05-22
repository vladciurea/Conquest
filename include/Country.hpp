#pragma once

#include <iostream>
#include <string>
#include <vector>

// Forward declaration: Country foloseste Player* dar nu are nevoie
// de definitia completa a lui Player in header.
// Definitia completa vine in Country.cpp unde chiar folosim metode ale Player.
class Player;

class Country {
    std::string          name;
    std::vector<Country*> neighbors;
    Player*              owner           = nullptr;
    int                  resourceProdIndex = 1;
    int                  resourceTier    = 1;

public:
    Country(std::string n,
            const std::vector<Country*>& neigh,
            Player* own,
            int prodIndex,
            int tier);

    Country(const Country& other);
    Country& operator=(const Country& other);
    ~Country();

    [[nodiscard]] const std::string& getName()  const;
    [[nodiscard]] int                getTier()   const;
    [[nodiscard]] Player*            getOwner()  const;

    void setOwner(Player* p);
    bool isNeighbor(const Country* c) const;

    [[nodiscard]] int productionPerTurn() const;
    [[nodiscard]] int costToBuy()         const;

    friend std::ostream& operator<<(std::ostream& os, const Country& c);
};