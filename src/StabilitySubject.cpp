#include "StabilitySubject.hpp"

StabilityLevel StabilitySubject::levelFor(float stability) {
    if (stability < 15.f) return StabilityLevel::Critical;
    if (stability < 30.f) return StabilityLevel::Warning;
    return StabilityLevel::Normal;
}

// cppcheck-suppress unusedFunction
void StabilitySubject::addObserver(StabilityObserver* obs) {
    if (obs) observers.push_back(obs);
}

// cppcheck-suppress unusedFunction
void StabilitySubject::notifyStability(float stability) {
    StabilityLevel current = levelFor(stability);
    if (current == lastLevel) return;
    lastLevel = current;
    for (auto* obs : observers)
        obs->onStabilityChanged(stability, current);
}