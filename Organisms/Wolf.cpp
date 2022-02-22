#include <iostream>

#include "Wolf.h"

// wolf has high strength value so it can dominate the world easily

Wolf::Wolf(const Point &position, World *world) : Animal(
        9, 5, "W", "Wolf", position, world) {}

Wolf::Wolf(int strength, const Point &position, World *world) : Animal(
        strength, 5, "W", "Wolf", position, world) {}

bool Wolf::sameSpecies(Organism *other) {
    return dynamic_cast<Wolf*>(other) != nullptr;
}

Organism *Wolf::reproduce(Point position) {
    return new Wolf(position, world);
}

Wolf::~Wolf() {

}


