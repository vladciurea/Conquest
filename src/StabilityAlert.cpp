#include "StabilityAlert.hpp"

StabilityAlert::StabilityAlert(const sf::Font& font)
    : alertText(font) {
    alertText.setCharacterSize(18);
    alertText.setStyle(sf::Text::Bold);
    alertText.setPosition({1080.f, 630.f});
}

void StabilityAlert::onStabilityChanged(float, StabilityLevel level) {
    switch (level) {
        case StabilityLevel::Critical:
            alertText.setString("GET YO\nSTABILITY UP\n NOT YO FUNNY UP");
            alertText.setFillColor(sf::Color(220, 40, 40));
            visible = true;
            break;
        case StabilityLevel::Warning:
            alertText.setString("Stabilitatea\n e cam\ncooked gang!");
            alertText.setFillColor(sf::Color(220, 180, 40));
            visible = true;
            break;
        case StabilityLevel::Normal:
            visible = false;
            break;
    }
}

void StabilityAlert::draw(sf::RenderWindow& window) const {
    if (visible) window.draw(alertText);
}