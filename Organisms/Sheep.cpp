#include "Sheep.h"

Sheep::Sheep(const Point &position, World *world) : Animal(
        4, 4, "S", "Sheep", position, world) {}

Sheep::Sheep(int strength, const Point &position, World *world) : Animal(
        strength, 4, "S", "Sheep", position, world) {}

bool Sheep::sameSpecies(Organism *other) {
    return dynamic_cast<Sheep*>(other) != nullptr;
}

Organism *Sheep::reproduce(Point position) {
    return new Sheep(position, world);
}

Sheep::~Sheep() {

}
