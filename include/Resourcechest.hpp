#pragma once

#include <string>
#include <vector>
#include <iostream>

class ResourceChest {
    std::string question;
    std::vector<std::string> options;
    int correctIndex = 0;

    static int totalChestsOpened;

public:
    ResourceChest(std::string q, const std::vector<std::string>& opts, int correct);

    ResourceChest(const ResourceChest& other);
    ResourceChest& operator=(const ResourceChest& other);
    virtual ~ResourceChest();

    [[nodiscard]] virtual ResourceChest* clone() const = 0;

    virtual void applyReward(float& gold, float& stability) const = 0;

    [[nodiscard]] virtual std::string getTypeName() const = 0;
    [[nodiscard]] virtual std::string getRewardDescription() const = 0;

    [[nodiscard]] bool checkAnswer(int answerIndex) const;

    static void registerOpened();
    [[nodiscard]] static int getTotalChestsOpened();

    [[nodiscard]] const std::string& getQuestion() const;
    [[nodiscard]] const std::vector<std::string>& getOptions() const;
    [[nodiscard]] int getCorrectIndex() const;

    friend std::ostream& operator<<(std::ostream& os, const ResourceChest& rc);

protected:
    virtual void displayInfo(std::ostream& os) const = 0;
};