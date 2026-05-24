#include "Sidepanel.hpp"

static constexpr float ICON_SIZE = 80.f;
static constexpr float SLOT_W   = 250.f;
static constexpr float POPUP_W  = 500.f;
static constexpr float POPUP_H  = 320.f;

ChestSlot::ChestSlot(const sf::Font& font, ResourceChest* c,
                     const std::string& imagePath, sf::Vector2f pos)
    : chest(c), nameText(font), timerText(font) {

    if (texture.loadFromFile(imagePath))
        icon.setTexture(&texture);

    icon.setSize({ICON_SIZE, ICON_SIZE});
    icon.setPosition(pos);
    icon.setOutlineThickness(2.f);
    icon.setOutlineColor(sf::Color(100, 100, 140));

    nameText.setCharacterSize(13);
    nameText.setFillColor(sf::Color(200, 200, 200));
    nameText.setString(chest->getTypeName());
    nameText.setPosition({pos.x + ICON_SIZE + 8.f, pos.y + 4.f});

    timerText.setCharacterSize(12);
    timerText.setFillColor(sf::Color(160, 160, 160));
    timerText.setPosition({pos.x + ICON_SIZE + 8.f, pos.y + 24.f});

    float barX = pos.x + ICON_SIZE + 8.f;
    float barY = pos.y + 44.f;
    float barW = SLOT_W - ICON_SIZE - 12.f;

    timerBar.setSize({barW, 8.f});
    timerBar.setPosition({barX, barY});
    timerBar.setFillColor(sf::Color(40, 40, 55));
    timerBar.setOutlineThickness(1.f);
    timerBar.setOutlineColor(sf::Color(70, 70, 90));

    timerBarFill.setPosition({barX, barY});
    timerBarFill.setFillColor(sf::Color(80, 130, 160));

    clock.restart();
}

void ChestSlot::update(float /*dt*/) {
    float elapsed = clock.getElapsedTime().asSeconds();
    float ratio = elapsed / COOLDOWN;
    if (ratio > 1.f) ratio = 1.f;
    available = (elapsed >= COOLDOWN);

    timerBarFill.setSize({timerBar.getSize().x * ratio, 8.f});

    if (available) {
        timerText.setString("Disponibil! Click pentru deschidere");
        timerText.setFillColor(sf::Color(100, 220, 100));
        icon.setOutlineColor(sf::Color(80, 200, 80));
        timerBarFill.setFillColor(sf::Color(80, 200, 80));
    } else {
        int remaining = static_cast<int>(COOLDOWN - elapsed) + 1;
        timerText.setString("Disponibil in " + std::to_string(remaining) + "s");
        timerText.setFillColor(sf::Color(160, 160, 160));
        icon.setOutlineColor(sf::Color(100, 100, 140));
        timerBarFill.setFillColor(sf::Color(80, 130, 160));
    }
}

void ChestSlot::draw(sf::RenderWindow& window) const {
    window.draw(icon);
    window.draw(nameText);
    window.draw(timerText);
    window.draw(timerBar);
    window.draw(timerBarFill);
}

void ChestSlot::resetTimer() {
    clock.restart();
    available = false;
}

bool ChestSlot::isAvailable()               const { return available; }
bool ChestSlot::containsIcon(sf::Vector2f p) const { return icon.getGlobalBounds().contains(p); }
bool ChestSlot::checkAnswer(int idx)         const { return chest->checkAnswer(idx); }
const ResourceChest& ChestSlot::getChest()  const { return *chest; }

void ChestSlot::applyReward(float& gold, float& stability) const {
    chest->applyReward(gold, stability);
}

ChestPopup::ChestPopup(const sf::Font& font)
    : questionText(font), rewardText(font),
      answerTexts{sf::Text(font), sf::Text(font), sf::Text(font)},
      closeText(font) {

    overlay.setSize({1280.f, 720.f});
    overlay.setPosition({0.f, 0.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    float bx = (1280.f - POPUP_W) / 2.f;
    float by = (720.f  - POPUP_H) / 2.f;

    box.setSize({POPUP_W, POPUP_H});
    box.setPosition({bx, by});
    box.setFillColor(sf::Color(30, 32, 45));
    box.setOutlineThickness(2.f);
    box.setOutlineColor(sf::Color(100, 100, 160));

    questionText.setCharacterSize(18);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition({bx + 20.f, by + 20.f});

    rewardText.setCharacterSize(14);
    rewardText.setFillColor(sf::Color(220, 190, 80));
    rewardText.setPosition({bx + 20.f, by + 55.f});

    for (int i = 0; i < 3; i++) {
        answerButtons[i].setSize({POPUP_W - 40.f, 44.f});
        answerButtons[i].setPosition({bx + 20.f, by + 85.f + i * 54.f});
        answerButtons[i].setFillColor(sf::Color(50, 55, 75));
        answerButtons[i].setOutlineThickness(1.f);
        answerButtons[i].setOutlineColor(sf::Color(100, 100, 150));

        answerTexts[i].setCharacterSize(15);
        answerTexts[i].setFillColor(sf::Color::White);
        answerTexts[i].setPosition({bx + 30.f, by + 97.f + i * 54.f});
    }

    closeButton.setSize({100.f, 36.f});
    closeButton.setPosition({bx + POPUP_W - 116.f, by + POPUP_H - 50.f});
    closeButton.setFillColor(sf::Color(90, 40, 40));
    closeButton.setOutlineThickness(1.f);
    closeButton.setOutlineColor(sf::Color(160, 80, 80));

    closeText.setCharacterSize(14);
    closeText.setFillColor(sf::Color::White);
    closeText.setString("Inchide");
    sf::FloatRect cb = closeText.getLocalBounds();
    sf::FloatRect rb = closeButton.getGlobalBounds();
    closeText.setOrigin({cb.size.x / 2.f, cb.size.y / 2.f});
    closeText.setPosition({rb.position.x + rb.size.x / 2.f,
                           rb.position.y + rb.size.y / 2.f - cb.size.y / 4.f});
}

void ChestPopup::show(int slotIdx, const ResourceChest& chest) {
    visible = true;
    chestSlotIdx = slotIdx;
    questionText.setString(chest.getQuestion());
    rewardText.setString("Recompensa: " + chest.getRewardDescription());
    const auto& opts = chest.getOptions();
    for (int i = 0; i < 3 && i < static_cast<int>(opts.size()); i++) {
        answerTexts[i].setString(std::to_string(i + 1) + ". " + opts[i]);
        answerButtons[i].setFillColor(sf::Color(50, 55, 75));
    }
}

void ChestPopup::hide() {
    visible = false;
    chestSlotIdx = -1;
}

void ChestPopup::markAnswer(int idx, bool correct) {
    if (idx >= 0 && idx < 3)
        answerButtons[idx].setFillColor(correct ? sf::Color(40, 130, 40) : sf::Color(130, 40, 40));
}

bool ChestPopup::isVisible()                      const { return visible; }
int  ChestPopup::getSlotIdx()                     const { return chestSlotIdx; }
bool ChestPopup::clickedClose(sf::Vector2f p)     const { return closeButton.getGlobalBounds().contains(p); }

int ChestPopup::getClickedAnswer(sf::Vector2f p) const {
    for (int i = 0; i < 3; i++)
        if (answerButtons[i].getGlobalBounds().contains(p)) return i;
    return -1;
}

void ChestPopup::draw(sf::RenderWindow& window) const {
    if (!visible) return;
    window.draw(overlay);
    window.draw(box);
    window.draw(questionText);
    window.draw(rewardText);
    for (int i = 0; i < 3; i++) {
        window.draw(answerButtons[i]);
        window.draw(answerTexts[i]);
    }
    window.draw(closeButton);
    window.draw(closeText);
}

SidePanel::SidePanel(const sf::Font& font)
    : font(font), chestsTitle(font), abilitiesTitle(font), popup(font) {

    background.setSize({PANEL_W, PANEL_H});
    background.setPosition({0.f, 0.f});
    background.setFillColor(sf::Color(22, 24, 35));
    background.setOutlineThickness(1.f);
    background.setOutlineColor(sf::Color(55, 55, 75));

    chestsTitle.setCharacterSize(14);
    chestsTitle.setFillColor(sf::Color(140, 160, 200));
    chestsTitle.setStyle(sf::Text::Bold);
    chestsTitle.setString("RESOURCE CHESTS");
    chestsTitle.setPosition({8.f, CHESTS_Y - 22.f});

    abilitiesTitle.setCharacterSize(14);
    abilitiesTitle.setFillColor(sf::Color(140, 160, 200));
    abilitiesTitle.setStyle(sf::Text::Bold);
    abilitiesTitle.setString("ABILITATI");
    abilitiesTitle.setPosition({8.f, 90.f});

    chestSlots.reserve(2);

    chestSlots.emplace_back(font,
        new GoldChest("Care este capitala Romaniei?",
            std::vector<std::string>{"Budapesta", "Sofia", "Bucuresti"}, 2, 500.f),
        "goldchest.jpg",
        sf::Vector2f{SLOT_X, CHESTS_Y});

    chestSlots.emplace_back(font,
        new StabilityChest("Care este cel mai mare oras din Germania?",
            std::vector<std::string>{"München", "Hamburg", "Berlin"}, 2, 15.f),
        "stabilitychest.jpg",
        sf::Vector2f{SLOT_X, CHESTS_Y + SLOT_H});
}

void SidePanel::rebuildAbilityButtons() {
    abilityButtons.clear();
    abilityTexts.clear();
    for (int i = 0; i < static_cast<int>(abilities.size()); i++) {
        sf::RectangleShape btn;
        btn.setSize({PANEL_W - 20.f, 52.f});
        btn.setPosition({10.f, 116.f + i * 60.f});
        btn.setFillColor(sf::Color(40, 55, 40));
        btn.setOutlineThickness(1.f);
        btn.setOutlineColor(sf::Color(70, 130, 70));
        abilityButtons.push_back(btn);

        sf::Text t(font);
        t.setCharacterSize(13);
        t.setFillColor(sf::Color::White);
        t.setString(abilities[i].getName() + "\nCost: "
            + std::to_string(abilities[i].getGoldCost()) + " aur | +"
            + std::to_string(abilities[i].getStabilityEffect()) + "% stab");
        t.setPosition({14.f, 122.f + i * 60.f});
        abilityTexts.push_back(t);
    }
}

void SidePanel::setAbilities(const std::vector<Ability>& abs) {
    abilities = abs;
    rebuildAbilityButtons();
}

SidePanelAction SidePanel::handleClick(sf::Vector2f mousePos,
                                        float& gold, float& stability) {
    if (popup.isVisible()) {
        if (popup.clickedClose(mousePos)) {
            popup.hide();
            return SidePanelAction::None;
        }
        int ans = popup.getClickedAnswer(mousePos);
        if (ans >= 0) {
            int idx = popup.getSlotIdx();
            bool correct = chestSlots[idx].checkAnswer(ans);
            popup.markAnswer(ans, correct);
            if (correct) chestSlots[idx].applyReward(gold, stability);
            chestSlots[idx].resetTimer();
            popup.hide();
            return SidePanelAction::ChestAnswered;
        }
        return SidePanelAction::None;
    }

    for (int i = 0; i < static_cast<int>(chestSlots.size()); i++) {
        if (chestSlots[i].isAvailable() && chestSlots[i].containsIcon(mousePos)) {
            popup.show(i, chestSlots[i].getChest());
            return SidePanelAction::None;
        }
    }

    for (int i = 0; i < static_cast<int>(abilityButtons.size()); i++) {
        if (abilityButtons[i].getGlobalBounds().contains(mousePos)) {
            if (gold >= static_cast<float>(abilities[i].getGoldCost())) {
                gold -= static_cast<float>(abilities[i].getGoldCost());
                stability += static_cast<float>(abilities[i].getStabilityEffect());
                if (stability > 100.f) stability = 100.f;
                abilities.erase(abilities.begin() + i);
                rebuildAbilityButtons();
                return SidePanelAction::AbilityUsed;
            }
        }
    }

    return SidePanelAction::None;
}

void SidePanel::update(float dt) {
    for (auto& slot : chestSlots)
        slot.update(dt);
}

void SidePanel::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(abilitiesTitle);
    window.draw(chestsTitle);
    for (const auto& slot : chestSlots)
        slot.draw(window);
    for (int i = 0; i < static_cast<int>(abilityButtons.size()); i++) {
        window.draw(abilityButtons[i]);
        window.draw(abilityTexts[i]);
    }
}

void SidePanel::drawPopup(sf::RenderWindow& window) const {
    popup.draw(window);
}