#pragma once

#include "Plant.h"

// Sow thistle is like grass, but it's 3 times more reproductive!

class SowThistle : public Plant {
public:
    SowThistle(const Point &position, World *world);

    void action() override;

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    ~SowThistle() override;
};
