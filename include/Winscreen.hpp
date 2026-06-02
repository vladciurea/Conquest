#pragma once

#include <SFML/Graphics.hpp>

class WinScreen {
    sf::Text titleText;
    sf::RectangleShape menuButton;
    sf::Text buttonText;

public:
    WinScreen(const sf::Font& font, sf::Vector2u windowSize);

    [[nodiscard]] bool clickedMenuButton(sf::Vector2f point) const;
    void updateHover(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window) const;
};