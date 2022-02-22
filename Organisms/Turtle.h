#pragma once

#include "Animal.h"

// animal which can move once per four turns at average. Also can reflect attack from attacker

class Turtle : public Animal {
public:
    Turtle(const Point &position, World *world);

    Turtle(int strength, const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    void action() override;

    bool collision(Organism *attacker) override;

    ~Turtle() override;
};
