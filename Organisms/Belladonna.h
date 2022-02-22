#pragma once

#include "Plant.h"

// Can kill animal if eaten

class Belladonna : public Plant {
public:
    Belladonna(const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    bool collision(Organism* attacker) override;

    ~Belladonna() override;;
};