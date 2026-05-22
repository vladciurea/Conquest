#pragma once

#include "Menu.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

// Starile posibile ale jocului
enum class GameState {
    Menu,
    Playing,
    Quit
};

class Game {
    sf::RenderWindow window;
    sf::Font font;
    sf::Clock clock;

    GameState state;
    std::unique_ptr<Menu> menu;

    // Constante fereastra
    static constexpr unsigned int WINDOW_WIDTH = 1280;
    static constexpr unsigned int WINDOW_HEIGHT = 720;
    static const std::string WINDOW_TITLE;
    static const std::string FONT_PATH;

    // Cele trei faze ale game loop-ului
    void processEvents();
    void update(float dt);
    void render();

    // Incarca fontul; arunca exceptie daca nu il gaseste
    void loadFont();

public:
    Game();
    ~Game() = default;


    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Porneste game loop-ul; se intoarce cand fereastra e inchisa
    void run();
};