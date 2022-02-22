#pragma once

#include "Animal.h"

// Antelope is jumping by 2 fields instead of 1 and has a chance to run from attacker
class Antelope : public Animal {
public:
    Antelope(const Point &position, World *world);

    Antelope(int strength, const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    void action() override;

    bool collision(Organism *attacker) override;

    ~Antelope() override;;
};
