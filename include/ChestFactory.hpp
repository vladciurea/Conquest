#pragma once

#include "Resourcechest.hpp"
#include "Repository.hpp"
#include <memory>
#include <vector>
#include <string>

class ChestFactory {
    static std::unique_ptr<ResourceChest> createFromFields(
        const std::string& type, float reward,
        const std::string& question,
        const std::vector<std::string>& options, int correct);

public:
    // Filtreaza chest-urile dupa tip ("gold" / "stability")
    [[nodiscard]] static Repository<ResourceChest>
        loadByType(const std::string& path, const std::string& type);
};