#pragma once

#include "Plant.h"

// Sosnowsky's hogweed, very dangerous plant which can kill anyone next to it and also kills if being eaten

class Hogweed : public Plant {
public:
    Hogweed(const Point &position, World *world);

    bool sameSpecies(Organism *other) override;

    Organism *reproduce(Point position) override;

    void action() override;

    bool collision(Organism* attacker) override;

    ~Hogweed() override;
};