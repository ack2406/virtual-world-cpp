#include "Turtle.h"

#define ACTION_CHANCE 4
#define SMALL_STRENGTH 5

Turtle::Turtle(const Point &position, World *world) : Animal( 2, 1, "Z", "Turtle",
                                                              position, world) {}

Turtle::Turtle(int strength, const Point &position, World *world) : Animal( strength, 1, "Z", "Turtle",
                                                              position, world) {}

bool Turtle::sameSpecies(Organism *other) {
    return dynamic_cast<Turtle*>(other) != nullptr;
}

Organism *Turtle::reproduce(Point position) {
    return new Turtle(position, world);
}

void Turtle::action() {
    if (!(rand() % ACTION_CHANCE)){ // do action every fourth move at average
        Animal::action();
    }
}

bool Turtle::collision(Organism *attacker) {
    if (strength > attacker->getStrength()){ // if defender is stronger than attacker
        if (attacker->getInvincibility() > 0){ // if attacker is immune, leave him
            world->addMessage(attacker->getName() + " reflected " + getName() + ".");
            return false;
        }
        else{ // kill attacker D:
            world->addMessage(getName() + " killed " + attacker->getName() + ".");
            world->popOrganism(attacker);
            return false;
        }
    }
    if (attacker->getStrength() < SMALL_STRENGTH) { // if attacker has less than 5 attack, reflect his attack
        world->addMessage(getName() + " reflected " + attacker->getName() + ".");
        return false;
    }
    world->addMessage(attacker->getName() + " killed " + getName() + ".");
    world->popOrganism(this);
    return true;
}

Turtle::~Turtle() {

}





