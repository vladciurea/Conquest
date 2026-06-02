#include "Winscreen.hpp"

static const sf::Color GOLD(220, 190, 80);
static const sf::Color BTN_NORMAL(70, 70, 90);
static const sf::Color BTN_HOVER(100, 100, 130);

WinScreen::WinScreen(const sf::Font& font, sf::Vector2u windowSize)
    : titleText(font), buttonText(font) {

    float centerX = static_cast<float>(windowSize.x) / 2.f;
    float centerY = static_cast<float>(windowSize.y) / 2.f;

    titleText.setString("Ai castigat!\nFie ca imperiul tau sa tina 1000 de ani!");
    titleText.setCharacterSize(40);
    titleText.setFillColor(GOLD);
    titleText.setStyle(sf::Text::Bold);
    {
        sf::FloatRect b = titleText.getLocalBounds();
        titleText.setOrigin({b.size.x / 2.f, b.size.y / 2.f});
        titleText.setPosition({centerX, centerY - 80.f});
    }

    sf::Vector2f btnSize = {300.f, 60.f};
    menuButton.setSize(btnSize);
    menuButton.setPosition({centerX - btnSize.x / 2.f, centerY + 60.f});
    menuButton.setFillColor(BTN_NORMAL);
    menuButton.setOutlineThickness(2.f);
    menuButton.setOutlineColor(GOLD);

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

bool WinScreen::clickedMenuButton(sf::Vector2f point) const {
    return menuButton.getGlobalBounds().contains(point);
}

void WinScreen::updateHover(sf::Vector2f mousePos) {
    menuButton.setFillColor(
        menuButton.getGlobalBounds().contains(mousePos) ? BTN_HOVER : BTN_NORMAL);
}

void WinScreen::draw(sf::RenderWindow& window) const {
    window.draw(titleText);
    window.draw(menuButton);
    window.draw(buttonText);
}