#pragma once

#include <iostream>
#include <string>
#include <vector>

class ResourceChest {
    std::string              question;
    std::vector<std::string> options;
    int                      correctIndex = 0;
    int                      rewardGold   = 100;
    int                      lifeTimeTurns = 5;

public:
    ResourceChest(std::string q,
                  const std::vector<std::string>& opts,
                  int correct,
                  int reward,
                  int life);

    // Afiseaza intrebarea, citeste raspunsul si returneaza recompensa
    // (0 daca raspunsul e gresit, rewardGold daca e corect).
    [[nodiscard]] int presentAndResolve() const;

    friend std::ostream& operator<<(std::ostream& os, const ResourceChest& rc);
};