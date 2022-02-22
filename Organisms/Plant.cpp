#include "Plant.h"

#define BREED_CHANCE 20

Plant::Plant(int strength, const std::string &symbol, const std::string &name, const Point &position, World *world) : Organism(
        strength, 0, symbol, name, position, world) {}


// breed more plants at random chance
void Plant::action() {
    if (!(rand() % BREED_CHANCE)) breed();
}

// collision from defender perspective
bool Plant::collision(Organism *attacker) {
    if (strength > attacker->getStrength()){ // if defender has more strength than attacker
        if (attacker->getInvincibility() > 0){ // // if attacker has invincibility enabled, deflect defender
            world->addMessage(attacker->getName() + " is immune to " + getName() + ".");
        }
        else{  // die to plant D:
            world->addMessage(attacker->getName() + " couldn't eat and died to " + getName() + ".");
            world->popOrganism(attacker);
        }
        return false;
    }
    else{ // if attacker has more strength than defender, eat this plant
        world->addMessage(attacker->getName() + " ate " + getName() + ".");
        world->popOrganism(this);
        return true;
    }
}

Plant::~Plant() {

}
