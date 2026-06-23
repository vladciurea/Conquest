#pragma once

#include "Repository.hpp"
#include "Goldchest.hpp"
#include "Stabilitychest.hpp"
#include "Ability.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <array>

enum class SidePanelAction {
    None,
    ChestAnswered,
    AbilityUsed
};

class ChestSlot {
    Repository<ResourceChest> variants;
    int currentVariant = 0;
    sf::Texture texture;
    sf::RectangleShape icon;
    sf::Text nameText;
    sf::Text timerText;
    sf::RectangleShape timerBar;
    sf::RectangleShape timerBarFill;
    sf::Clock clock;
    bool available = false;

    static constexpr float COOLDOWN = 30.f;

public:
    ChestSlot(const sf::Font& font, Repository<ResourceChest> chestVariants,
              const std::string& imagePath, sf::Vector2f pos);

    ChestSlot(const ChestSlot&) = delete;
    ChestSlot& operator=(const ChestSlot&) = delete;
    ChestSlot(ChestSlot&&) = default;
    ChestSlot& operator=(ChestSlot&&) = default;

    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    void drawPopup(sf::RenderWindow& window) const;
    void resetTimer();

    [[nodiscard]] bool isAvailable() const;
    [[nodiscard]] bool containsIcon(sf::Vector2f p) const;
    [[nodiscard]] bool checkAnswer(int idx) const;
    void applyReward(float& gold, float& stability) const;
    [[nodiscard]] const ResourceChest& getChest() const;
    void pickRandomVariant();
    [[nodiscard]] int getTotalOptionsCount() const;
};

class ChestPopup {
    bool visible = false;
    int chestSlotIdx = -1;

    sf::RectangleShape overlay;
    sf::RectangleShape box;
    sf::Text questionText;
    sf::Text rewardText;
    std::array<sf::RectangleShape, 3> answerButtons;
    std::array<sf::Text, 3> answerTexts;
    sf::RectangleShape closeButton;
    sf::Text closeText;

public:
    explicit ChestPopup(const sf::Font& font);

    void show(int slotIdx, const ResourceChest& chest);
    void hide();
    void draw(sf::RenderWindow& window) const;

    [[nodiscard]] bool isVisible() const;
    [[nodiscard]] int getSlotIdx() const;
    [[nodiscard]] int getClickedAnswer(sf::Vector2f p) const;
    [[nodiscard]] bool clickedClose(sf::Vector2f p) const;
    void markAnswer(int idx, bool correct);
};

class SidePanel {
    static constexpr float PANEL_W  = 270.f;
    static constexpr float PANEL_H  = 720.f;
    static constexpr float CHESTS_Y = 400.f;
    static constexpr float SLOT_H   = 120.f;
    static constexpr float SLOT_X   = 10.f;

    const sf::Font& font;

    sf::RectangleShape background;
    sf::Text chestsTitle;
    sf::Text abilitiesTitle;

    std::vector<ChestSlot> chestSlots;
    ChestPopup popup;

    std::vector<Ability> abilities;
    std::vector<sf::RectangleShape> abilityButtons;
    std::vector<sf::Text> abilityTexts;
    std::vector<bool> abilityOwned;

    void rebuildAbilityButtons();

public:
    explicit SidePanel(const sf::Font& font);

    SidePanel(const SidePanel&) = delete;
    SidePanel& operator=(const SidePanel&) = delete;

    void setAbilities(const std::vector<Ability>& abs);
    void resetAbilities();
    SidePanelAction handleClick(sf::Vector2f mousePos, float& gold, float& stability);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    void drawPopup(sf::RenderWindow& window) const;
};