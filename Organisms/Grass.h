#pragma once

#include "Plant.h"

// basic plant without ambition to be better, it's just growing and sometimes is being eaten

class Grass : public Plant {
public:
    Grass(const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    ~Grass() override;
};