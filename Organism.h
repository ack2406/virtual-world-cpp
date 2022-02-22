#pragma once

#include <string>

#include "Point.h"
#include "World.h"
class World;

// Basic class for every specie in the simulation

class Organism {
protected:
    int strength; // determines if can kill or eat other organism
    int initiative; // determines order of organisms action
    std::string symbol; // symbol of organism
    std::string name; // full name of organism
    Point position; // determines position in the world
    World *world; // pointer to world where organism exists
    int invincibility = -5; // used for human ability only in this version of simulation
public:
    Organism(int strength, int initiative, const std::string &symbol, const std::string &name, const Point &position, World *world);

    int getStrength() const;

    void setStrength(int strength);

    int getInitiative() const;

    void setInitiative(int initiative);

    int getInvincibility() const;

    void setInvincibility(int invincibility);

    const Point &getPosition() const;

    void setPosition(const Point &position);

    World *getWorld() const;

    void setWorld(World *world);

    const std::string &getSymbol() const;

    void setSymbol(const std::string &symbol);

    // non getters or setters methods

    virtual void action() = 0;

    virtual bool collision(Organism* attacker) = 0;

    virtual void draw();

    virtual Organism *reproduce(Point position) = 0;

    virtual bool sameSpecies(Organism *other) = 0;

    std::string getName();

    void breed();

    virtual ~Organism();
};