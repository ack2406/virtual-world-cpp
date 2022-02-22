#include "Belladonna.h"

Belladonna::Belladonna(const Point &position, World *world) : Plant(99, "B", "Belladonna", position, world) {}

bool Belladonna::sameSpecies(Organism *other) {
    return dynamic_cast<Belladonna*>(other) != nullptr;
}

Organism *Belladonna::reproduce(Point position) {
    return new Belladonna(position, world);
}

bool Belladonna::collision(Organism *attacker) {
    world->popOrganism(this); // 'eat' belladonna
    if (attacker->getInvincibility() > 0){
        world->addMessage(attacker->getName() + " is immune to " + getName() + ".");
        return true;
    }
    else{ // die if not immune D:
        world->addMessage(attacker->getName() + " ate and also died to " + getName() + ".");
        world->popOrganism(attacker);
        return false;
    }

}

Belladonna::~Belladonna() {

}
