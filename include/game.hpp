#pragma once

#include "menu.hpp"
#include "Gamescreen.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

enum class GameState {
    Menu,
    Playing,
    Quit
};

class Game {
    sf::RenderWindow window;
    sf::Font         font;
    sf::Clock        clock;

    GameState                  state;
    std::unique_ptr<Menu>       menu;
    std::unique_ptr<GameScreen> gameScreen;

    static constexpr unsigned int WINDOW_WIDTH  = 1280;
    static constexpr unsigned int WINDOW_HEIGHT = 720;
    static const     std::string  WINDOW_TITLE;
    static const     std::string  FONT_PATH;

    void processEvents();
    void update(float dt);
    void render();
    void loadFont();

    // Tranzitii intre stari
    void startGame();
    void backToMenu();

public:
    Game();
    ~Game() = default;

    Game(const Game&)            = delete;
    Game& operator=(const Game&) = delete;

    void run();
};