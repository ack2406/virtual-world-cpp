#include "Guarana.h"

Guarana::Guarana(const Point &position, World *world) : Plant(0, "G", "Guarana", position, world) {}

bool Guarana::collision(Organism *attacker) { // if eaten, give bonus to strength to eater
    attacker->setStrength(attacker->getStrength() + 3);
    world->addMessage(attacker->getName() + " get 3 points of strength from eating " + getName() + ".");
    world->popOrganism(this);
    return true;
}

bool Guarana::sameSpecies(Organism *other) {
    return dynamic_cast<Guarana*>(other) != nullptr;
}

Organism *Guarana::reproduce(Point position) {
    return new Guarana(position, world);
}

Guarana::~Guarana() {

}
