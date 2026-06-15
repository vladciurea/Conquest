#include "ChestFactory.hpp"
#include "Goldchest.hpp"
#include "Stabilitychest.hpp"
#include "Gameexceptions.hpp"

#include <fstream>
#include <sstream>

std::unique_ptr<ResourceChest> ChestFactory::createFromFields(
    const std::string& type, float reward,
    const std::string& question,
    const std::vector<std::string>& options, int correct) {

    if (type == "gold")
        return std::make_unique<GoldChest>(question, options, correct, reward);
    if (type == "stability")
        return std::make_unique<StabilityChest>(question, options, correct, reward);
    return nullptr;
}

std::vector<std::unique_ptr<ResourceChest>>
ChestFactory::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw ResourceException("deschidere fisier " + path, 0, 1);

    std::vector<std::unique_ptr<ResourceChest>> result;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string type, rewardStr, question;
        std::vector<std::string> options;
        std::string token;

        std::getline(ss, type, ';');
        std::getline(ss, rewardStr, ';');
        std::getline(ss, question, ';');

        std::string opt0, opt1, opt2, correctStr;
        std::getline(ss, opt0, ';');
        std::getline(ss, opt1, ';');
        std::getline(ss, opt2, ';');
        std::getline(ss, correctStr, ';');

        options = {opt0, opt1, opt2};
        float reward = std::stof(rewardStr);
        int correct  = std::stoi(correctStr);

        auto chest = createFromFields(type, reward, question, options, correct);
        if (chest) result.push_back(std::move(chest));
    }

    return result;
}

std::vector<std::unique_ptr<ResourceChest>>
ChestFactory::loadByType(const std::string& path, const std::string& type) {
    std::ifstream file(path);
    if (!file.is_open())
        throw ResourceException("deschidere fisier " + path, 0, 1);

    std::vector<std::unique_ptr<ResourceChest>> result;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string lineType, rewardStr, question;
        std::getline(ss, lineType, ';');
        if (lineType != type) continue;

        std::getline(ss, rewardStr, ';');
        std::getline(ss, question, ';');

        std::string opt0, opt1, opt2, correctStr;
        std::getline(ss, opt0, ';');
        std::getline(ss, opt1, ';');
        std::getline(ss, opt2, ';');
        std::getline(ss, correctStr, ';');

        std::vector<std::string> options = {opt0, opt1, opt2};
        float reward = std::stof(rewardStr);
        int correct  = std::stoi(correctStr);

        auto chest = createFromFields(type, reward, question, options, correct);
        if (chest) result.push_back(std::move(chest));
    }

    return result;
}