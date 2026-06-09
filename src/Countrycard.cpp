#include "Countrycard.hpp"
#include "Gameexceptions.hpp"
#include <sstream>
#include <iomanip>

static constexpr float CARD_HEIGHT = 180.f;
static constexpr float BUTTON_W    = 120.f;
static constexpr float BUTTON_H    = 40.f;
static constexpr float SEG_H       = 10.f;
static constexpr float SEG_GAP     = 3.f;

CountryCard::CountryCard(Country* c, const sf::Font& font, sf::Vector2f pos, float w)
    : country(c), nameText(font), typeText(font), incomeText(font),
      buttonText(font), costText(font) {

    background.setSize({w, CARD_HEIGHT});
    background.setPosition(pos);
    background.setOutlineThickness(2.f);

    flagSprite.setSize({w, CARD_HEIGHT});
    flagSprite.setPosition(pos);

    float segW = (w - 2 * SEG_GAP - (MAX_LEVEL - 1) * SEG_GAP) / MAX_LEVEL;
    for (int i = 0; i < MAX_LEVEL; i++) {
        upgradeSegments[i].setSize({segW, SEG_H});
        upgradeSegments[i].setPosition({
            pos.x + SEG_GAP + i * (segW + SEG_GAP),
            pos.y + CARD_HEIGHT - SEG_H - 8.f
        });
    }

    actionButton.setSize({BUTTON_W, BUTTON_H});
    actionButton.setPosition({
        pos.x + w / 2.f - BUTTON_W / 2.f,
        pos.y + CARD_HEIGHT - BUTTON_H - 28.f
    });
    actionButton.setOutlineThickness(1.f);
    actionButton.setOutlineColor(sf::Color(180, 180, 180));

    nameText.setCharacterSize(20);
    nameText.setFillColor(sf::Color::White);
    nameText.setStyle(sf::Text::Bold);
    nameText.setPosition({pos.x + 10.f, pos.y + 8.f});

    typeText.setCharacterSize(13);
    typeText.setFillColor(sf::Color(180, 180, 180));
    typeText.setPosition({pos.x + 10.f, pos.y + 34.f});

    incomeText.setCharacterSize(14);
    incomeText.setFillColor(sf::Color(220, 190, 80));
    incomeText.setPosition({pos.x + 10.f, pos.y + 55.f});

    costText.setCharacterSize(15);
    costText.setFillColor(sf::Color(220, 190, 80));
    costText.setPosition({pos.x + 10.f, pos.y + 78.f});

    buttonText.setCharacterSize(14);
    buttonText.setFillColor(sf::Color::White);

    nameText.setString(country->getName());
    typeText.setString(country->getTypeName());
    updateVisuals(1.f);
}

void CountryCard::centerText(sf::Text& text, const sf::RectangleShape& rect) {
    sf::FloatRect tb = text.getLocalBounds();
    sf::FloatRect rb = rect.getGlobalBounds();
    text.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
    text.setPosition({
        rb.position.x + rb.size.x / 2.f,
        rb.position.y + rb.size.y / 2.f - tb.size.y / 4.f
    });
}

void CountryCard::updateVisuals(float stability) {
    bool owned = isOwned();

    if (owned) {
        background.setFillColor(sf::Color(40, 50, 40, 230));
        background.setOutlineColor(sf::Color(80, 160, 80));

        float realIncome = static_cast<float>(country->produceIncome(stability / 100.f))
                           * getProductionMultiplier();
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1)
            << realIncome << " aur/sec (Nivel " << upgradeLevel << ")";
        incomeText.setString(oss.str());

        if (!isMaxLevel()) {
            actionButton.setFillColor(sf::Color(50, 110, 50));
            buttonText.setString("Upgrade\n" + std::to_string(getUpgradeCost()) + " aur");
            costText.setString("");
        } else {
            actionButton.setFillColor(sf::Color(50, 50, 50));
            buttonText.setString("MAXIM");
            costText.setString("");
        }

        for (int i = 0; i < MAX_LEVEL; i++)
            upgradeSegments[i].setFillColor(
                i < upgradeLevel ? sf::Color(80, 200, 80) : sf::Color(50, 50, 50));

    } else {
        background.setFillColor(sf::Color(30, 30, 38, 230));
        background.setOutlineColor(sf::Color(80, 80, 80));
        incomeText.setString("");
        actionButton.setFillColor(sf::Color(110, 80, 20));
        buttonText.setString("Cumpara");
        costText.setString("Cost: " + std::to_string(country->costToBuy()) + " aur");

        for (int i = 0; i < MAX_LEVEL; i++)
            upgradeSegments[i].setFillColor(sf::Color(35, 35, 35));
    }
    centerText(buttonText, actionButton);
}

void CountryCard::setFlag(const sf::Texture* texture) {
    if (texture) {
        flagTexture = texture;
        flagSprite.setTexture(flagTexture);
        flagSprite.setFillColor(sf::Color(255, 255, 255, 50));
        flagLoaded = true;
    }
}

bool CountryCard::isOwned()    const { return country->isOwned(); }
bool CountryCard::isMaxLevel() const { return upgradeLevel >= MAX_LEVEL; }
int  CountryCard::getLevel()   const { return upgradeLevel; }

float CountryCard::getProductionMultiplier() const {
    // Nivel 1 = 1x, nivel 2 = 1.8x, nivel 3 = 3x, nivel 4 = 5x, nivel 5 = 8x
    // Crestere semnificativa dar nu exponentiala pura
    static constexpr float multipliers[5] = {1.f, 1.8f, 3.f, 5.f, 8.f};
    int idx = upgradeLevel - 1;
    if (idx < 0) idx = 0;
    if (idx > 4) idx = 4;
    return multipliers[idx];
}
bool CountryCard::containsPoint(sf::Vector2f point) const {
    return background.getGlobalBounds().contains(point);
}

int CountryCard::getUpgradeCost() const {
    return country->costToBuy() / 4 * upgradeLevel;
}

void CountryCard::upgrade() {
    if (isMaxLevel())
        throw CountryException(country->getName(), "tara este deja la nivel maxim");
    upgradeLevel++;
}

void CountryCard::unlock() {
    updateVisuals(1.f);
}

bool CountryCard::handleClick(sf::Vector2f mousePos, float& gold) {
    if (!actionButton.getGlobalBounds().contains(mousePos))
        return false;
    if (!isOwned() || isMaxLevel())
        return false;

    int cost = getUpgradeCost();
    if (gold < static_cast<float>(cost))
        throw ResourceException("upgrade " + country->getName(),
                                static_cast<int>(gold), cost);
    gold -= static_cast<float>(cost);
    upgrade();
    return true;
}

void CountryCard::update(float stability) {
    updateVisuals(stability);
}

void CountryCard::draw(sf::RenderWindow& window) const {
    window.draw(background);
    if (flagLoaded && flagTexture) window.draw(flagSprite);
    window.draw(nameText);
    window.draw(typeText);
    window.draw(incomeText);
    window.draw(costText);
    window.draw(actionButton);
    window.draw(buttonText);
    for (int i = 0; i < MAX_LEVEL; i++)
        window.draw(upgradeSegments[i]);
}