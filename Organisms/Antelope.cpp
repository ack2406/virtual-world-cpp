#include <iostream>
#include "Antelope.h"

#define DIRECTIONS 4

#define BREED_CHANCE 3
#define RUN_CHANCE 2

Antelope::Antelope(const Point &position, World *world)
        : Animal(4, 4, "A", "Antelope", position, world) {}

Antelope::Antelope(int strength, const Point &position, World *world)
        : Animal(strength, 4, "A", "Antelope", position, world) {}

bool Antelope::sameSpecies(Organism *other) {
    return dynamic_cast<Antelope*>(other) != nullptr;
}

Organism *Antelope::reproduce(Point position) {
    return new Antelope(position, world);
}

void Antelope::action() {
    int direction = rand() % DIRECTIONS;

    int x = position.getX();
    int y = position.getY();
    int moveValue = rand() % 2 + 1;

    switch (direction) {
        case 0 : // North
            (y > moveValue - 1) ? y -= moveValue : y += moveValue;
            break;
        case 1 : // South
            (y < world->getHeight() - moveValue) ? y += moveValue : y -= moveValue;
            break;
        case 2: // West
            (x > moveValue - 1) ? x -= moveValue : x += moveValue;
            break;
        case 3: // East
            (x < world->getWidth() - moveValue) ? x += moveValue : x -= moveValue;
            break;
        default:
            break;
    }
    Organism *other = world->getBoard()[y][x];
    if (other != nullptr) { // if field is not empty
        if (!sameSpecies(other)) { // and not same species
            if (other->collision(this)){ // if attacker succeeded, go to new field
                world->setBoardCell({position.getX(), position.getY()}, nullptr);
                setPosition({x, y});
                world->setBoardCell({position.getX(), position.getY()}, this);
            }
        }
        else{ // breed!
            if (!(rand() % BREED_CHANCE)) breed();
        }
    }
    else{ // if field is empty, go there without any problems
        world->setBoardCell({position.getX(), position.getY()}, nullptr);
        setPosition({x, y});
        world->setBoardCell({position.getX(), position.getY()}, this);
    }
}

bool Antelope::collision(Organism *attacker) {
    if (!(rand() % RUN_CHANCE)){ // has 50% chance to run from danger
        world->addMessage(getName() + " escaped from " + attacker->getName() + ".");
        int dx, dy, tries = 0;
        do{
            int dir = rand() % DIRECTIONS;
            tries++;

            dx = position.getX();
            dy = position.getY();

            switch (dir) {
                case 0 : // North
                    (dy > 0) ? dy-- : dy++;
                    break;
                case 1 : // South
                    (dy < world->getHeight() - 1) ? dy++ : dy--;
                    break;
                case 2: // West
                    (dx > 0) ? dx-- : dx++;
                    break;
                case 3: // East
                    (dx < world->getWidth() - 1) ? dx++ : dx--;
                    break;
                default:
                    break;
            }
        } while (world->getBoard()[dy][dx] != nullptr && tries < 4);
        if (world->getBoard()[dy][dx] == nullptr){ // if found new field, go there, otherwise, stand still and pray
            world->setBoardCell({position.getX(), position.getY()}, nullptr);
            setPosition({dx, dy});
            world->setBoardCell({position.getX(), position.getY()}, this);
        }
        return true;
    }
    return Animal::collision(attacker);
}

Antelope::~Antelope() {

}
