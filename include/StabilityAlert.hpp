#pragma once

#include "StabilityObserver.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class StabilityAlert : public StabilityObserver {
    sf::Text alertText;
    bool visible = false;

public:
    explicit StabilityAlert(const sf::Font& font);

    void onStabilityChanged(float stability, StabilityLevel level) override;
    void draw(sf::RenderWindow& window) const;
};