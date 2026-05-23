#pragma once

#include "AgriculturalCountry.hpp"
#include "IndustrialCountry.hpp"
#include "MilitaryCountry.hpp"
#include "Player.hpp"
#include "Ability.hpp"
#include "ResourceChest.hpp"
#include "GameExceptions.hpp"
#include "StabilityBar.hpp"
#include "CountryCard.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

enum class GameScreenResult {
    Continue,
    BackToMenu,
    GameOver,
    Victory
};

class GameScreen {
    std::vector<std::unique_ptr<Country>> countries;
    std::vector<CountryCard> cards;
    Player player;

    float gold = 0.f;
    float stability = 100.f;
    int unlockedUpTo = 0;

    const sf::Font& font;

    sf::Text goldText;
    StabilityBar stabilityBar;

    std::unique_ptr<Country> romaniaSnapshot;
    std::unordered_map<std::string, sf::Texture> flagTextures;

    void initCountries();
    void initPlayer();
    void initCards();
    void updateGold(float dt);
    void updateStability(float dt);
    void tryBuyCountry(int index);

public:
    explicit GameScreen(const sf::Font& font);
    GameScreen(const GameScreen& other);
    GameScreen& operator=(GameScreen other);
    ~GameScreen();

    GameScreen(GameScreen&&) = delete;
    GameScreen& operator=(GameScreen&&) = delete;

    [[nodiscard]] GameScreenResult handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void render(sf::RenderWindow& window);
    void reset();
};