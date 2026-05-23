#pragma once

#include <SFML/Graphics.hpp>

class StabilityBar {
    sf::RectangleShape background;
    sf::RectangleShape fill;
    sf::Text label;
    float width;
    float height;

public:
    StabilityBar(const sf::Font& font, sf::Vector2f position, float width, float height);

    void update(float stability);
    void draw(sf::RenderWindow& window) const;
};