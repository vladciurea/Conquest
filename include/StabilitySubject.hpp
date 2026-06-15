#pragma once

#include "StabilityObserver.hpp"
#include <vector>

class StabilitySubject {
    std::vector<StabilityObserver*> observers;
    StabilityLevel lastLevel = StabilityLevel::Normal;

    [[nodiscard]] static StabilityLevel levelFor(float stability);

public:
    void addObserver(StabilityObserver* obs);

    // Verifica stabilitatea si notifica observatorii doar cand se schimba categoria
    void notifyStability(float stability);
};