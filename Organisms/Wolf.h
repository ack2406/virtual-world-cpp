#pragma once

#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(const Point &position, World *world);

    Wolf(int strength, const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    ~Wolf() override;
};