#include "Hogweed.h"

Hogweed::Hogweed(const Point &position, World *world) : Plant(10, "X", "Hogweed", position, world) {}

bool Hogweed::sameSpecies(Organism *other) {
    return dynamic_cast<Plant*>(other) != nullptr;
}

Organism *Hogweed::reproduce(Point position) {
    return new Hogweed(position, world);
}

bool Hogweed::collision(Organism *attacker) {
    world->addMessage(attacker->getName() + " ate " + getName() + ".");
    world->popOrganism(this); // be eaten and take eater with you
    if (attacker->getInvincibility() > 0){ // unless he is immune to death!
        world->addMessage(attacker->getName() + " is immune to " + getName() + ".");
        return true;
    }
    else{
        world->popOrganism(attacker);
        return false;
    }

}

void Hogweed::action() {
    Plant::action(); // Do what normal plant would do - reproduce! and...
    for (int i = -1; i < 2; i++){ // look for near positions if there are any animals, and kill them D:
        for (int j = -1; j < 2; j++){
            if (i == 0 && j == 0) continue; // it's me!
            if (position.getY() + j >= 0 && position.getY() + j < world->getHeight() && position.getX() + i >= 0 &&
                    position.getX() + i < world->getWidth()){
                Organism *other = world->getBoard()[position.getY() + j][position.getX() + i];
                if (other != nullptr && !sameSpecies(other)){
                    if (other->getInvincibility() > 0){
                        world->addMessage(other->getName() + " is immune to hogweed.");
                    }
                    else{
                        world->addMessage(other->getName() + " was killed by hogweed.");
                        world->popOrganism(other);
                    }
                }
            }

        }
    }
}

Hogweed::~Hogweed() {

}
