#pragma once

#include "Animal.h"

// basic animal without any special power, sheep just eats grass and that's it

class Sheep : public Animal {
public:
    Sheep(const Point &position, World *world);

    Sheep(int strength, const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    ~Sheep() override;
};
