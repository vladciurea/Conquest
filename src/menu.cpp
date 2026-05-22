#include "Menu.hpp"

// ---------------------------------------------------------------
// Button
// ---------------------------------------------------------------
Button::Button(const sf::Font& font,
               const std::string& text,
               sf::Vector2f position,
               sf::Vector2f size,
               unsigned int charSize)
    : label(font) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(70, 70, 90));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color(150, 150, 180));

    label.setString(text);
    label.setCharacterSize(charSize);
    label.setFillColor(sf::Color::White);

    // Centram textul in interiorul dreptunghiului
    const sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin({textBounds.size.x / 2.f, textBounds.size.y / 2.f});
    label.setPosition({
        position.x + size.x / 2.f,
        position.y + size.y / 2.f - textBounds.size.y / 4.f
    });
}

bool Button::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

void Button::setColor(sf::Color color) {
    shape.setFillColor(color);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(label);
}

Menu::Menu(const sf::Font& font, sf::Vector2u windowSize) : titleText(font) {
    const float centerX  = static_cast<float>(windowSize.x) / 2.f;
    const float centerY  = static_cast<float>(windowSize.y) / 2.f;
    const sf::Vector2f btnSize = {280.f, 60.f};

    // Titlu
    titleText.setString("Conquest");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color(220, 200, 140));  // auriu
    titleText.setStyle(sf::Text::Bold);
    {
        const sf::FloatRect b = titleText.getLocalBounds();
        titleText.setOrigin({b.size.x / 2.f, b.size.y / 2.f});
        titleText.setPosition({centerX, centerY - 160.f});
    }

    // Buton Start Game (index 0)
    buttons.emplace_back(font, "Start Game",
        sf::Vector2f{centerX - btnSize.x / 2.f, centerY - 20.f},
        btnSize);

    // Buton Quit (index 1)
    buttons.emplace_back(font, "Quit",
        sf::Vector2f{centerX - btnSize.x / 2.f, centerY + 70.f},
        btnSize);
    buttons[1].setColor(COLOR_QUIT);
}

MenuAction Menu::handleEvent(const sf::Event& event,
                              sf::RenderWindow& window) const {
    // In SFML 3, MouseButtonReleased e accesat prin getIf<>()
    if (const auto* mouseBtn = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseBtn->button == sf::Mouse::Button::Left) {
            const sf::Vector2f mousePos = window.mapPixelToCoords(
                {mouseBtn->position.x, mouseBtn->position.y});

            if (buttons[0].contains(mousePos)) return MenuAction::StartGame;
            if (buttons[1].contains(mousePos)) return MenuAction::Quit;
        }
    }
    return MenuAction::None;
}

void Menu::update(sf::Vector2f mousePos) {
    // Hover pe Start Game
    buttons[0].setColor(buttons[0].contains(mousePos) ? COLOR_HOVER : COLOR_NORMAL);
    // Hover pe Quit
    buttons[1].setColor(buttons[1].contains(mousePos) ? COLOR_QUIT_HV : COLOR_QUIT);
}

void Menu::draw(sf::RenderWindow& window) const {
    window.draw(titleText);
    for (const auto& btn : buttons) {
        btn.draw(window);
    }
}