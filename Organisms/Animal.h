#pragma once

#include "../Organism.h"

// class for every moving organism

class Animal : public Organism{
public:
    Animal(int strength, int initiative, const std::string &symbol, const std::string &name, const Point &position, World *world);

    void action() override;

    bool collision(Organism* attacker) override;

    ~Animal() override;

};