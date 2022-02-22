#pragma once

#include "Animal.h"

// User controllable "animal" with special ability to be immune to damage from every source

class Human : public Animal {
public:
    Human(const Point &position, World *world);

    Human(int strength, const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    void action() override;

    void becomeInvincible();

    ~Human() override;
};