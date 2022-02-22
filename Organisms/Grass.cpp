#include "Grass.h"

Grass::Grass(const Point &position, World *world) : Plant(0, "/", "Grass", position, world) {}

bool Grass::sameSpecies(Organism *other) {
    return dynamic_cast<Grass*>(other) != nullptr;
}

Organism *Grass::reproduce(Point position) {
    return new Grass(position, world);
}

Grass::~Grass() {

}


