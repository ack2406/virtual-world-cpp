#pragma once

#include "Plant.h"

// plant which can give eater a bonus to strength

class Guarana : public Plant {
public:
    Guarana(const Point &position, World *world);

    bool collision(Organism* attacker) override;

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    ~Guarana() override;
};