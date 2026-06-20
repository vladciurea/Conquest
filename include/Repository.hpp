#pragma once

#include <memory>
#include <vector>
#include <functional>

template <typename T>
class Repository {
    std::vector<std::unique_ptr<T>> items;

public:
    Repository() = default;

    Repository(const Repository&) = delete;
    Repository& operator=(const Repository&) = delete;
    Repository(Repository&&) noexcept = default;
    Repository& operator=(Repository&&) noexcept = default;

    void add(std::unique_ptr<T> item) {
        if (item) items.push_back(std::move(item));
    }

    void clear() { items.clear(); }
    void reserve(std::size_t n) { items.reserve(n); }

    [[nodiscard]] std::size_t size() const { return items.size(); }
    [[nodiscard]] bool empty() const { return items.empty(); }

    [[nodiscard]] T* at(std::size_t index) const {
        if (index >= items.size()) return nullptr;
        return items[index].get();
    }

    [[nodiscard]] Repository<T> cloneAll() const {
        Repository<T> copy;
        copy.reserve(items.size());
        for (const auto& item : items)
            copy.add(std::unique_ptr<T>(item->clone()));
        return copy;
    }

    [[nodiscard]] int countIf(const std::function<bool(const T&)>& pred) const {
        int n = 0;
        for (const auto& item : items)
            if (pred(*item)) n++;
        return n;
    }

    [[nodiscard]] bool allOf(const std::function<bool(const T&)>& pred) const {
        for (const auto& item : items)
            if (!pred(*item)) return false;
        return true;
    }

    void forEach(const std::function<void(T&)>& fn) {
        for (auto& item : items)
            fn(*item);
    }
};

template <typename T>
[[nodiscard]] float sumOver(const Repository<T>& repo,
                            const std::function<float(const T&)>& extractor) {
    float total = 0.f;
    for (std::size_t i = 0; i < repo.size(); i++) {
        const T* item = repo.at(i);
        if (item) total += extractor(*item);
    }
    return total;
}