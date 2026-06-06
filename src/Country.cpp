#include "Country.hpp"

#include <algorithm>

Country::Country(std::string n,
                 const std::vector<Country*>& neigh,
                 Player* own,
                 int prodIndex,
                 int tier)
    : name(std::move(n)), neighbors(neigh),
      resourceTier(tier), owner(own), resourceProdIndex(prodIndex) {}

Country::Country(const Country& other)
    : name(other.name),
      neighbors(other.neighbors),
      resourceTier(other.resourceTier),
      owner(other.owner),
      resourceProdIndex(other.resourceProdIndex) {
    std::cout << "[Country] Copy constructor pentru " << name << '\n';
}

Country& Country::operator=(const Country& other) {
    if (this != &other) {
        name              = other.name;
        neighbors         = other.neighbors;
        resourceTier      = other.resourceTier;
        owner             = other.owner;
        resourceProdIndex = other.resourceProdIndex;
    }
    std::cout << "[Country] operator= pentru " << name << '\n';
    return *this;
}

Country::~Country() {
    std::cout << "[Country] Destructor pentru " << name << '\n';
}

// NVI: operator<< este non-virtual si apeleaza displayInfo() virtual
std::ostream& operator<<(std::ostream& os, const Country& c) {
    c.displayInfo(os);
    return os;
}

const std::string& Country::getName()  const { return name; }
int                Country::getTier()   const { return resourceTier; }
Player*            Country::getOwner()  const { return owner; }

void Country::setOwner(Player* p) { owner = p; }

// bool Country::isNeighbor(const Country* c) const {
//     return std::ranges::any_of(neighbors,
//                                [c](const Country* n){ return n == c; });
// }

// Productia de baza comuna - derivatele o folosesc ca punct de plecare
int Country::baseProduction() const {
    return resourceProdIndex * resourceTier * (10 + resourceTier);
}