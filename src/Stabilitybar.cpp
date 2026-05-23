#include "Stabilitybar.hpp"

StabilityBar::StabilityBar(const sf::Font& font, sf::Vector2f position, float w, float h)
    : label(font), width(w), height(h) {
    background.setSize({w, h});
    background.setPosition(position);
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color(100, 100, 100));

    fill.setSize({w, h});
    fill.setPosition(position);

    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);
    label.setPosition({position.x, position.y - 22.f});
    label.setString("Stabilitate: 100%");
}

void StabilityBar::update(float stability) {
    float ratio = stability / 100.f;
    if (ratio < 0.f) ratio = 0.f;
    if (ratio > 1.f) ratio = 1.f;

    fill.setSize({width * ratio, height});

    if (stability > 60.f)
        fill.setFillColor(sf::Color(60, 180, 60));
    else if (stability > 30.f)
        fill.setFillColor(sf::Color(200, 180, 0));
    else
        fill.setFillColor(sf::Color(200, 50, 50));

    label.setString("Stabilitate: " + std::to_string(static_cast<int>(stability)) + "%");
}

void StabilityBar::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(fill);
    window.draw(label);
}