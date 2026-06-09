#include "Country.hpp"
#include "Gameexceptions.hpp"

Country::Country(std::string n,
                 const std::vector<Country*>& neigh,
                 bool isOwnedInit,
                 int prodIndex,
                 int tier)
    : name(std::move(n)), neighbors(neigh),
      resourceTier(tier), owned(isOwnedInit), resourceProdIndex(prodIndex) {
    if (tier < 1)
        throw CountryException(name, "tier invalid (< 1): " + std::to_string(tier));
    if (prodIndex < 1)
        throw CountryException(name, "prodIndex invalid (< 1): " + std::to_string(prodIndex));
}

Country::Country(const Country& other)
    : name(other.name),
      neighbors(other.neighbors),
      resourceTier(other.resourceTier),
      owned(other.owned),
      resourceProdIndex(other.resourceProdIndex) {
    std::cout << "[Country] Copy constructor pentru " << name << '\n';
}

Country& Country::operator=(const Country& other) {
    if (this != &other) {
        name              = other.name;
        neighbors         = other.neighbors;
        resourceTier      = other.resourceTier;
        owned             = other.owned;
        resourceProdIndex = other.resourceProdIndex;
    }
    std::cout << "[Country] operator= pentru " << name << '\n';
    return *this;
}

Country::~Country() {
    std::cout << "[Country] Destructor pentru " << name << '\n';
}

std::ostream& operator<<(std::ostream& os, const Country& c) {
    c.displayInfo(os);
    return os;
}

const std::string& Country::getName()  const { return name; }
int                Country::getTier()   const { return resourceTier; }
bool               Country::isOwned()  const { return owned; }

void Country::setOwned(bool value) { owned = value; }

int Country::baseProduction() const {
    return resourceProdIndex * resourceTier * (10 + resourceTier);
}