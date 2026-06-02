#include "game.hpp"

#include <iostream>
#include <stdexcept>

const std::string Game::WINDOW_TITLE = "Conquest";
const std::string Game::FONT_PATH    = "DejaVuSans.ttf";

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
             WINDOW_TITLE,
             sf::Style::Default),
      state(GameState::Menu) {
    window.setVerticalSyncEnabled(true);
    loadFont();
    menu = std::make_unique<Menu>(font, window.getSize());
    std::cout << "[Game] Initializat.\n";
}

void Game::loadFont() {
    if (!font.openFromFile(FONT_PATH)) {
        throw std::runtime_error(
            "[Game] Nu s-a putut incarca fontul: " + FONT_PATH);
    }
    std::cout << "[Game] Font incarcat: " << FONT_PATH << "\n";
}

void Game::run() {
    std::cout << "[Game] Game loop pornit.\n";
    while (window.isOpen() && state != GameState::Quit) {
        const float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
    window.close();
    std::cout << "[Game] Game loop oprit.\n";
}

void Game::startGame() {
    std::cout << "[Game] Pornire joc.\n";
    // Cream GameScreen doar la primul start sau dupa reset
    if (!gameScreen) {
        gameScreen = std::make_unique<GameScreen>(font);
    } else {
        gameScreen->reset();
    }
    state = GameState::Playing;
}

void Game::backToMenu() {
    std::cout << "[Game] Inapoi la meniu.\n";
    state = GameState::Menu;
    // Nu distrugem gameScreen - il pastram pentru a putea relua
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            state = GameState::Quit;
            return;
        }
        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape) {
                if (state == GameState::Playing || state == GameState::Won
                    || state == GameState::Dead) backToMenu();
                else state = GameState::Quit;
                return;
            }
        }

        if (state == GameState::Menu && menu) {
            const MenuAction action = menu->handleEvent(*event, window);
            if (action == MenuAction::Quit) {
                state = GameState::Quit;
            } else if (action == MenuAction::StartGame) {
                startGame();
            }
        } else if (state == GameState::Won && winScreen) {
            if (const auto* click = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (click->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        {click->position.x, click->position.y});
                    if (winScreen->clickedMenuButton(mousePos)) backToMenu();
                }
            }
        } else if (state == GameState::Dead && deathScreen) {
            if (const auto* click = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (click->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        {click->position.x, click->position.y});
                    if (deathScreen->clickedMenuButton(mousePos)) backToMenu();
                }
            }
        } else if (state == GameState::Playing && gameScreen) {
            const GameScreenResult result =
                gameScreen->handleEvent(*event, window);
            if (result == GameScreenResult::BackToMenu) backToMenu();
            else if (result == GameScreenResult::GameOver)  backToMenu();
            else if (result == GameScreenResult::Victory)   backToMenu();
        }
    }
}

void Game::update(float dt) {
    if (state == GameState::Menu && menu) {
        const sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));
        menu->update(mousePos);
    } else if (state == GameState::Won && winScreen) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        winScreen->updateHover(mousePos);
    } else if (state == GameState::Dead && deathScreen) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        deathScreen->updateHover(mousePos);
    } else if (state == GameState::Playing && gameScreen) {
        gameScreen->update(dt);
        if (gameScreen->isGameWon()) {
            std::cout << "[Game] Joc castigat!\n";
            winScreen = std::make_unique<WinScreen>(font, window.getSize());
            state = GameState::Won;
        } else if (gameScreen->isGameOver()) {
            std::cout << "[Game] Game over - imperiul a colapsat.\n";
            deathScreen = std::make_unique<DeathScreen>(font, window.getSize());
            state = GameState::Dead;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(20, 24, 32));

    if (state == GameState::Menu && menu) {
        menu->draw(window);
    } else if (state == GameState::Playing && gameScreen) {
        gameScreen->render(window);
    } else if (state == GameState::Won && winScreen) {
        winScreen->draw(window);
    } else if (state == GameState::Dead && deathScreen) {
        if (gameScreen) gameScreen->render(window);
        deathScreen->draw(window);
    }

    window.display();
}