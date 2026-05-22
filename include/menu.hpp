#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Actiunile posibile returnate de Menu::handleEvent()
enum class MenuAction {
    None,       // niciun eveniment relevant
    StartGame,  // userul a apasat Start Game (deocamdata nefunctional)
    Quit        // userul a apasat Quit
};

// Un buton simplu: dreptunghi colorat + text centrat
struct Button {
    sf::RectangleShape shape;
    sf::Text           label;

    Button(const sf::Font& font,
           const std::string& text,
           sf::Vector2f position,
           sf::Vector2f size,
           unsigned int charSize = 28);

    // Verifica daca pozitia (ex: mouse) e in interiorul butonului
    [[nodiscard]] bool contains(sf::Vector2f point) const;

    // Seteaza culoarea fundalului butonului
    void setColor(sf::Color color);

    void draw(sf::RenderWindow& window) const;
};

class Menu {
    std::vector<Button> buttons; // 0 = Start, 1 = Quit
    sf::Text titleText;

    // Culorile butoanelor
    static constexpr sf::Color COLOR_NORMAL = sf::Color(70,  70,  90);
    static constexpr sf::Color COLOR_HOVER = sf::Color(100, 100, 130);
    static constexpr sf::Color COLOR_QUIT = sf::Color(120, 50,  50);
    static constexpr sf::Color COLOR_QUIT_HV = sf::Color(160, 70,  70);

public:
    Menu(const sf::Font& font, sf::Vector2u windowSize);

    // Proceseaza un eveniment SFML si returneaza actiunea corespunzatoare
    [[nodiscard]] MenuAction handleEvent(const sf::Event& event,
                                         sf::RenderWindow& window) const;

    // Actualizeaza hover-ul pe butoane in functie de pozitia mouse-ului
    void update(sf::Vector2f mousePos);

    void draw(sf::RenderWindow& window) const;
};