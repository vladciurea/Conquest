#include "Country.hpp"

#include <algorithm>

Country::Country(std::string n,
                 const std::vector<Country*>& neigh,
                 Player* own,
                 int prodIndex,
                 int tier)
    : name(std::move(n)), neighbors(neigh), owner(own),
      resourceProdIndex(prodIndex), resourceTier(tier) {}

Country::Country(const Country& other)
    : name(other.name),
      neighbors(other.neighbors),
      owner(other.owner),
      resourceProdIndex(other.resourceProdIndex),
      resourceTier(other.resourceTier) {
    std::cout << "[Country] Copy constructor pentru " << name << '\n';
}

Country& Country::operator=(const Country& other) {
    if (this != &other) {
        name              = other.name;
        neighbors         = other.neighbors;
        owner             = other.owner;
        resourceProdIndex = other.resourceProdIndex;
        resourceTier      = other.resourceTier;
    }
    std::cout << "[Country] operator= pentru " << name << '\n';
    return *this;
}

Country::~Country() {
    std::cout << "[Country] Destructor pentru " << name << '\n';
}

const std::string& Country::getName()  const { return name; }
int                Country::getTier()   const { return resourceTier; }
Player*            Country::getOwner()  const { return owner; }

void Country::setOwner(Player* p) { owner = p; }

bool Country::isNeighbor(const Country* c) const {
    return std::ranges::any_of(neighbors,
                               [c](const Country* n){ return n == c; });
}

int Country::productionPerTurn() const {
    return resourceProdIndex * resourceTier * (10 + resourceTier);
}

int Country::costToBuy() const {
    return 50 * resourceTier + productionPerTurn() * 2;
}

std::ostream& operator<<(std::ostream& os, const Country& c) {
    os << "Country[" << c.name << "] tier=" << c.resourceTier
       << " prodIndex=" << c.resourceProdIndex
       << " owner=" << (c.owner ? "Player" : "None");
    return os;
}