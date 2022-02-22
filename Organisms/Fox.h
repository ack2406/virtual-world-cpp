#pragma once

#include "Animal.h"

// Fox knows where the danger is and will never go to field where is standing stronger organism
class Fox : public Animal {
public:
    Fox(const Point &position, World *world);

    Fox(int strength, const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    void action() override;

    ~Fox() override;
};