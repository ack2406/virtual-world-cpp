#pragma once

#include "../Organism.h"

// class for every static organism

class Plant : public Organism {
public:
    Plant(int strength, const std::string &symbol, const std::string &name, const Point &position, World *world);

    void action() override;

    bool collision(Organism* attacker) override;

    ~Plant() override;
};