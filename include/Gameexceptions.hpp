#pragma once

#include <stdexcept>
#include <string>



class GameException : public std::exception {
    std::string message;

public:
    explicit GameException(std::string msg)
        : message(std::move(msg)) {}

    // std::exception::what() este const noexcept in standard
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};


class ResourceException : public GameException {
    int goldAvailable;
    int goldRequired;

public:
    ResourceException(const std::string& action,
                      int available,
                      int required)
        : GameException("ResourceException: " + action +
                        " (disponibil=" + std::to_string(available) +
                        ", necesar=" + std::to_string(required) + ")"),
          goldAvailable(available),
          goldRequired(required) {}

    // [[nodiscard]] int getGoldAvailable() const noexcept { return goldAvailable; }
    // [[nodiscard]] int getGoldRequired()  const noexcept { return goldRequired; }

    // cppcheck-suppress unusedFunction
    [[nodiscard]] int getDeficit()       const noexcept { return goldRequired - goldAvailable; }
};



class CountryException : public GameException {
    std::string countryName;

public:
    CountryException(const std::string& countryName,
                     const std::string& reason)
        : GameException("CountryException [" + countryName + "]: " + reason),
          countryName(countryName) {}

    // cppcheck-suppress unusedFunction
    [[nodiscard]] const std::string& getCountryName() const noexcept {
        return countryName;
    }
};


class StabilityException : public GameException {
    float stabilityValue;

public:
    StabilityException(const std::string& reason, float value)
        : GameException("StabilityException: " + reason +
                        " (valoare=" + std::to_string(value) + ")"),
          stabilityValue(value) {}

    // [[nodiscard]] float getStabilityValue() const noexcept { return stabilityValue; }

    // cppcheck-suppress unusedFunction
    [[nodiscard]] bool isCollapse() const noexcept { return stabilityValue <= 0.0f; }
};