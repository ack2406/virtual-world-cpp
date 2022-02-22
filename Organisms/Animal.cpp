#include <iostream>
#include "Animal.h"

#define DIRECTIONS 4
#define CHANCE_TO_BREED 3

Animal::Animal(int strength, int initiative, const std::string &symbol, const std::string &name, const Point &position, World *world) : Organism(
        strength, initiative, symbol, name, position, world) {}

// basic things that organism does
void Animal::action() {
    // choosing direction where organism will move
    int direction = rand() % DIRECTIONS;

    int x = position.getX();
    int y = position.getY();

    switch (direction) {
        case 0 : // North
            (y > 0) ? y-- : y++;
            break;
        case 1 : // South
            (y < world->getHeight() - 1) ? y++ : y--;
            break;
        case 2: // West
            (x > 0) ? x-- : x++;
            break;
        case 3: // East
            (x < world->getWidth() - 1) ? x++ : x--;
            break;
        default:
            break;
    }
    Organism *other = world->getBoard()[y][x];
    if (other != nullptr) { // if field is occupied and not same species - attack, if same - breed, if not occupied - move
        if (!sameSpecies(other)) {
            if (other->collision(this)){ // if attacker succeeded, move his position to new field
                world->setBoardCell({position.getX(), position.getY()}, nullptr);
                setPosition({x, y});
                world->setBoardCell({position.getX(), position.getY()}, this);
            }
        }
        else{
            if (!(rand() % CHANCE_TO_BREED)) breed();
        }
    }
    else{ // if field is not occupied, move there
        world->setBoardCell({position.getX(), position.getY()}, nullptr);
        setPosition({x, y});
        world->setBoardCell({position.getX(), position.getY()}, this);
    }

}

// collision from defender perspective
bool Animal::collision(Organism *attacker) {
    if (strength > attacker->getStrength()){ // if defender has more strength than attacker
        if (attacker->getInvincibility() > 0){ // if attacker has invincibility enabled, deflect defender
            world->addMessage(attacker->getName() + " deflected " + getName() + ".");
        }
        else{ // kill attacker D:
            world->addMessage(getName() + " killed " + attacker->getName() + ".");
            world->popOrganism(attacker);
        }
        return false;
    }
    else{ // if attacker has more strength than defender
        if (getInvincibility() > 0){ // if defender has invincibility enabled, deflect attacker
            world->addMessage(getName() + " deflected " + attacker->getName() + ".");
            return false;
        }
        else{ // kill defender D:
            world->addMessage(attacker->getName() + " killed " + getName() + ".");
            world->popOrganism(this);
        }

        return true;
    }
}

Animal::~Animal() {

}


