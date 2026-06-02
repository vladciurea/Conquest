#include "Deathscreen.hpp"

static const sf::Color WASTED_RED(180, 20, 20);
static const sf::Color BTN_NORMAL(60, 30, 30);
static const sf::Color BTN_HOVER(100, 50, 50);

DeathScreen::DeathScreen(const sf::Font& font, sf::Vector2u windowSize)
    : wastedText(font), subtitleText(font), buttonText(font) {

    float w = static_cast<float>(windowSize.x);
    float h = static_cast<float>(windowSize.y);
    float centerX = w / 2.f;
    float centerY = h / 2.f;

    overlay.setSize({w, h});
    overlay.setPosition({0.f, 0.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 200));

    wastedText.setString("WASTED");
    wastedText.setCharacterSize(110);
    wastedText.setFillColor(WASTED_RED);
    wastedText.setStyle(sf::Text::Bold);
    {
        sf::FloatRect b = wastedText.getLocalBounds();
        wastedText.setOrigin({b.size.x / 2.f, b.size.y / 2.f});
        wastedText.setPosition({centerX, centerY - 60.f});
    }

    subtitleText.setString("Imperiul tau s-a prabusit in haos...");
    subtitleText.setCharacterSize(24);
    subtitleText.setFillColor(sf::Color(180, 180, 180));
    {
        sf::FloatRect b = subtitleText.getLocalBounds();
        subtitleText.setOrigin({b.size.x / 2.f, b.size.y / 2.f});
        subtitleText.setPosition({centerX, centerY + 30.f});
    }

    sf::Vector2f btnSize = {300.f, 60.f};
    menuButton.setSize(btnSize);
    menuButton.setPosition({centerX - btnSize.x / 2.f, centerY + 90.f});
    menuButton.setFillColor(BTN_NORMAL);
    menuButton.setOutlineThickness(2.f);
    menuButton.setOutlineColor(WASTED_RED);

    buttonText.setString("Inapoi la meniu");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    {
        sf::FloatRect tb = buttonText.getLocalBounds();
        sf::FloatRect rb = menuButton.getGlobalBounds();
        buttonText.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
        buttonText.setPosition({rb.position.x + rb.size.x / 2.f,
                                rb.position.y + rb.size.y / 2.f - tb.size.y / 4.f});
    }
}

bool DeathScreen::clickedMenuButton(sf::Vector2f point) const {
    return menuButton.getGlobalBounds().contains(point);
}

void DeathScreen::updateHover(sf::Vector2f mousePos) {
    menuButton.setFillColor(
        menuButton.getGlobalBounds().contains(mousePos) ? BTN_HOVER : BTN_NORMAL);
}

void DeathScreen::draw(sf::RenderWindow& window) const {
    window.draw(overlay);
    window.draw(wastedText);
    window.draw(subtitleText);
    window.draw(menuButton);
    window.draw(buttonText);
}