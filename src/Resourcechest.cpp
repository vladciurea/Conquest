#include "Resourcechest.hpp"

ResourceChest::ResourceChest(std::string q, const std::vector<std::string>& opts, int correct)
    : question(std::move(q)), options(opts), correctIndex(correct) {}

ResourceChest::ResourceChest(const ResourceChest& other)
    : question(other.question), options(other.options), correctIndex(other.correctIndex) {}

ResourceChest& ResourceChest::operator=(const ResourceChest& other) {
    if (this != &other) {
        question = other.question;
        options = other.options;
        correctIndex = other.correctIndex;
    }
    return *this;
}

ResourceChest::~ResourceChest() = default;

bool ResourceChest::checkAnswer(int answerIndex) const {
    return answerIndex == correctIndex;
}

const std::string& ResourceChest::getQuestion() const { return question; }
const std::vector<std::string>& ResourceChest::getOptions() const { return options; }
int ResourceChest::getCorrectIndex() const { return correctIndex; }

std::ostream& operator<<(std::ostream& os, const ResourceChest& rc) {
    rc.displayInfo(os);
    return os;
}