#include "StabilitySubject.hpp"
#include <algorithm>

StabilityLevel StabilitySubject::levelFor(float stability) {
    if (stability < 15.f) return StabilityLevel::Critical;
    if (stability < 30.f) return StabilityLevel::Warning;
    return StabilityLevel::Normal;
}

void StabilitySubject::addObserver(StabilityObserver* obs) {
    if (obs) observers.push_back(obs);
}

void StabilitySubject::removeObserver(StabilityObserver* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs),
                    observers.end());
}

void StabilitySubject::notifyStability(float stability) {
    StabilityLevel current = levelFor(stability);
    if (current == lastLevel) return;
    lastLevel = current;
    for (auto* obs : observers)
        obs->onStabilityChanged(stability, current);
}