#pragma once

#include "Country.hpp"

// Tara industriala: venit mare, dar scade stabilitatea imperiului
// cu fiecare tick (poluare, nemultumire muncitoreasca).
// Caracteristica speciala: pollutionRate - cat de mult scade stabilitatea.
class IndustrialCountry : public Country {
    float pollutionRate;    // cat scade stabilitatea pe tick (ex: 0.5f)
    int   factoryLevel;     // nivelul fabricilor, amplifica productia

public:
    IndustrialCountry(std::string n,
                      const std::vector<Country*>& neigh,
                      bool isOwnedInit,
                      int prodIndex,
                      int tier,
                      float pollution = 0.3f,
                      int factories   = 1);

    IndustrialCountry(const IndustrialCountry& other);
    IndustrialCountry& operator=(const IndustrialCountry& other);
    ~IndustrialCountry() override;

    [[nodiscard]] IndustrialCountry* clone() const override;

    // Specific temei: venitul e amplificat de factoryLevel
    // dar scade proportional cu instabilitatea
    [[nodiscard]] int produceIncome(float stabilityFactor) const override;

    // Mai scumpa decat agricultural, mai ieftina decat military
    [[nodiscard]] int costToBuy() const override;

    [[nodiscard]] std::string getTypeName() const override;

    void displayInfo(std::ostream& os) const override;

    // Specific tipului: returneaza cat scade stabilitatea per tick
    [[nodiscard]] float getPollutionRate() const;

    // Upgrade fabrici - creste productia dar si poluarea
    [[nodiscard]] int getFactoryLevel() const;
};