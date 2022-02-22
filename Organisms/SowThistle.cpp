#include "SowThistle.h"

SowThistle::SowThistle(const Point &position, World *world) : Plant(0, "*", "Sow Thistle", position, world) {}

bool SowThistle::sameSpecies(Organism *other) {
    return dynamic_cast<SowThistle*>(other) != nullptr;
}

Organism *SowThistle::reproduce(Point position) {
    return new SowThistle(position, world);
}

void SowThistle::action() { // try to reproduce 3 times!
    for (int i = 0; i < 3; i++){
        Plant::action();
    }
}

SowThistle::~SowThistle() {

}

