#pragma once

#include "Country.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class CountryCard {
    Country* country;
    int upgradeLevel = 1;
    static constexpr int MAX_LEVEL = 5;

    sf::RectangleShape background;
    sf::RectangleShape flagSprite;
    const sf::Texture* flagTexture = nullptr;
    sf::RectangleShape upgradeSegments[MAX_LEVEL];
    sf::RectangleShape actionButton;
    sf::Text nameText;
    sf::Text typeText;
    sf::Text incomeText;
    sf::Text buttonText;
    sf::Text costText;

    bool flagLoaded = false;

    void updateVisuals(float stability);
    void centerText(sf::Text& text, const sf::RectangleShape& rect);

public:
    CountryCard(Country* country, const sf::Font& font, sf::Vector2f position, float width);

    [[nodiscard]] bool isOwned() const;
    [[nodiscard]] bool isMaxLevel() const;
    [[nodiscard]] int getUpgradeCost() const;
    [[nodiscard]] int getLevel() const;
    [[nodiscard]] float getProductionMultiplier() const;

    void upgrade();
    void unlock();

    bool handleClick(sf::Vector2f mousePos, float& gold);
    [[nodiscard]] bool containsPoint(sf::Vector2f point) const;
    void update(float stability);
    void draw(sf::RenderWindow& window) const;

    void setFlag(const sf::Texture* texture);
};