#include "Gamescreen.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iostream>

static constexpr float CARDS_LEFT_X  = 290.f;
static constexpr float CARDS_RIGHT_X = 660.f;
static constexpr float CARDS_Y       = 80.f;
static constexpr float CARD_W        = 340.f;
static constexpr float CARD_GAP      = 200.f;

static const std::string FLAG_EXT = ".png";
static const std::vector<std::string> FLAG_NAMES = {"ro","bg","hu","gr","de","fr"};

void GameScreen::initCountries() {
    countries.clear();
    countries.push_back(std::make_unique<AgriculturalCountry>(
        "Romania",  std::vector<Country*>{}, false, 1, 1, 1.0f));
    countries.push_back(std::make_unique<IndustrialCountry>(
        "Bulgaria", std::vector<Country*>{}, false, 2, 1, 0.15f, 1));
    countries.push_back(std::make_unique<MilitaryCountry>(
        "Ungaria",  std::vector<Country*>{}, false, 2, 2, 1.0f, 1));
    countries.push_back(std::make_unique<AgriculturalCountry>(
        "Grecia",   std::vector<Country*>{}, false, 3, 3, 1.5f));
    countries.push_back(std::make_unique<IndustrialCountry>(
        "Germania", std::vector<Country*>{}, false, 3, 4, 0.3f, 2));
    countries.push_back(std::make_unique<TechCountry>(
        "Franta",   std::vector<Country*>{}, false, 3, 5, 6.0f, 3));

    romaniaSnapshot.reset(countries[0]->clone());
    countries[0]->setOwned(true);
}

void GameScreen::initState() {
    gold = 50.f;
    stability = 100.f;
    unlockedUpTo = 0;
}

void GameScreen::initCards() {
    cards.clear();
    flagTextures.clear();
    for (int i = 0; i < static_cast<int>(countries.size()); i++) {
        const std::string& name = FLAG_NAMES[i];
        sf::Texture tex;
        if (tex.loadFromFile(name + FLAG_EXT))
            flagTextures[name] = std::move(tex);
        float x = (i < 3) ? CARDS_LEFT_X : CARDS_RIGHT_X;
        float y = CARDS_Y + (i % 3) * CARD_GAP;
        cards.emplace_back(countries[i].get(), font, sf::Vector2f{x, y}, CARD_W);
        auto it = flagTextures.find(name);
        if (it != flagTextures.end())
            cards.back().setFlag(&it->second);
    }
}

GameScreen::GameScreen(const sf::Font& font)
    : font(font),
      goldText(font),
      stabilityBar(font, {15.f, 50.f}, 250.f, 24.f),
      sidePanel(font),
      stabilityAlert(font) {
    stabilitySubject.addObserver(&stabilityAlert);
    goldText.setCharacterSize(28);
    goldText.setFillColor(sf::Color(220, 190, 80));
    goldText.setPosition({640.f, 16.f});
    initState();
    initCountries();
    initCards();
    std::vector<Ability> abil = {
        Ability("PeoplePleaser", "Incetineste scaderea stabilitatii", 80, +8),
        Ability("MilitaryPower", "Productie x1.5", 120, +0)
    };
    sidePanel.setAbilities(abil);
}

GameScreen::GameScreen(const GameScreen& other)
    : gold(other.gold),
      stability(other.stability),
      unlockedUpTo(other.unlockedUpTo),
      gameWon(other.gameWon),
      gameOver(other.gameOver),
      font(other.font),
      goldText(other.goldText),
      stabilityBar(other.stabilityBar),
      sidePanel(other.font),
      stabilityAlert(other.font) {
    stabilitySubject.addObserver(&stabilityAlert);
    for (const auto& c : other.countries)
        countries.push_back(std::unique_ptr<Country>(c->clone()));
    if (other.romaniaSnapshot)
        romaniaSnapshot.reset(other.romaniaSnapshot->clone());
    initCards();
}

GameScreen& GameScreen::operator=(GameScreen other) {
    std::swap(gold, other.gold);
    std::swap(stability, other.stability);
    std::swap(unlockedUpTo, other.unlockedUpTo);
    std::swap(gameWon, other.gameWon);
    std::swap(gameOver, other.gameOver);
    std::swap(countries, other.countries);
    std::swap(romaniaSnapshot, other.romaniaSnapshot);
    std::swap(goldText, other.goldText);
    std::swap(stabilityBar, other.stabilityBar);
    std::swap(cards, other.cards);
    std::swap(flagTextures, other.flagTextures);
    return *this;
}

GameScreen::~GameScreen() {
    std::cout << "[GameScreen] Distrus.\n";
}

void GameScreen::reset() {
    GameScreen fresh(font);
    *this = fresh;
}

bool GameScreen::isGameWon() const { return gameWon; }
bool GameScreen::isGameOver() const { return gameOver; }

void GameScreen::tryBuyCountry(int index) {
    if (index <= 0 || index >= static_cast<int>(countries.size())) return;
    if (countries[index]->isOwned()) return;
    if (index > unlockedUpTo + 1) return;

    int cost = countries[index]->costToBuy();
    if (gold < static_cast<float>(cost))
        throw ResourceException("cumparare " + countries[index]->getName(),
                                static_cast<int>(gold), cost);
    gold -= static_cast<float>(cost);
    countries[index]->setOwned(true);
    unlockedUpTo = index;
    cards[index].unlock();
}

GameScreenResult GameScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (key->scancode == sf::Keyboard::Scancode::Escape)
            return GameScreenResult::BackToMenu;
    }

    if (const auto* click = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (click->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(
                {click->position.x, click->position.y});

            SidePanelAction action = sidePanel.handleClick(mousePos, gold, stability);
            if (action != SidePanelAction::None) return GameScreenResult::Continue;

            for (int i = 0; i < static_cast<int>(cards.size()); i++) {
                try {
                    if (cards[i].isOwned()) {
                        if (cards[i].handleClick(mousePos, gold)) break;
                    } else if (i == unlockedUpTo + 1) {
                        if (cards[i].containsPoint(mousePos)) {
                            tryBuyCountry(i);
                            break;
                        }
                    }
                } catch (const ResourceException& e) {
                    std::cerr << e.what() << "\n";
                } catch (const CountryException& e) {
                    std::cerr << e.what() << "\n";
                }
            }
        }
    }
    return GameScreenResult::Continue;
}

void GameScreen::updateGold(float dt) {
    float incomePerSec = 0.f;
    for (int i = 0; i < static_cast<int>(countries.size()); i++) {
        if (countries[i]->isOwned()) {
            float base = static_cast<float>(
                countries[i]->produceIncome(stability / 100.f));
            incomePerSec += base * cards[i].getProductionMultiplier();
        }
    }
    gold += incomePerSec * 4.0f * dt;

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << gold << " aur";
    goldText.setString(oss.str());
    const sf::FloatRect b = goldText.getLocalBounds();
    goldText.setOrigin({b.size.x / 2.f, 0.f});
}

void GameScreen::updateStability(float dt) {
    float decayRate = 0.2f * static_cast<float>(
        std::count_if(countries.begin(), countries.end(),
            [](const std::unique_ptr<Country>& c){ return c->isOwned(); }));

    float bonusRate = 0.f;
    for (const auto& c : countries) {
        if (c->isOwned()) {
            if (const auto* mil = dynamic_cast<const MilitaryCountry*>(c.get()))
                bonusRate += mil->stabilityBonus();
            if (const auto* ind = dynamic_cast<const IndustrialCountry*>(c.get()))
                decayRate += ind->getPollutionRate();
        }
    }

    sidePanel.update(dt);
    stability -= (decayRate - bonusRate) * dt;
    if (stability > 100.f) stability = 100.f;
    stabilityBar.update(stability);
    stabilitySubject.notifyStability(stability);

    if (stability <= 0.f) {
        stability = 0.f;
        throw StabilityException("Imperiul a colapsat", stability);
    }
}

void GameScreen::update(float dt) {
    try {
        updateGold(dt);
        updateStability(dt);
        for (auto& card : cards)
            card.update(stability);

        bool allMaxed = std::all_of(cards.begin(), cards.end(),
            [](const CountryCard& c){ return c.isOwned() && c.isMaxLevel(); });
        if (allMaxed) {
            std::cout << "[GameScreen] Victorie! Toate tarile maxate.\n";
            gameWon = true;
        }

    } catch (const StabilityException& e) {
        std::cerr << e.what() << "\n";
        gameOver = true;
    }
}

void GameScreen::render(sf::RenderWindow& window) {
    sidePanel.draw(window);
    stabilityBar.draw(window);
    window.draw(goldText);
    stabilityAlert.draw(window);
    for (const auto& card : cards)
        card.draw(window);
    sidePanel.drawPopup(window);
}