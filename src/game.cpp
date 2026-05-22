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
    std::cout << "[Game] Initializat. Fereastra: "
              << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << "\n";
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

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        // Inchidere prin X sau Escape - merge indiferent de stare
        if (event->is<sf::Event::Closed>()) {
            state = GameState::Quit;
            return;
        }
        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape) {
                state = GameState::Quit;
                return;
            }
        }

        // Delegam evenimentul catre starea curenta
        if (state == GameState::Menu && menu) {
            const MenuAction action = menu->handleEvent(*event, window);
            if (action == MenuAction::Quit) {
                std::cout << "[Game] Quit apasat din meniu.\n";
                state = GameState::Quit;
            } else if (action == MenuAction::StartGame) {
                std::cout << "[Game] Start Game apasat (deocamdata nefunctional).\n";
                // state = GameState::Playing; -- de activat la v0.2
            }
        }
    }
}


void Game::update(float /*dt*/) {
    if (state == GameState::Menu && menu) {
        // Pasam pozitia mouse-ului pentru hover pe butoane
        const sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));
        menu->update(mousePos);
    }
}


void Game::render() {
    window.clear(sf::Color(20, 24, 32));

    if (state == GameState::Menu && menu) {
        menu->draw(window);
    }
    // Aici vom adauga randarea jocului cand GameState::Playing e implementat

    window.display();
}