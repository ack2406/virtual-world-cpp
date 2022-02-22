#include <iostream>
#include "Fox.h"

#define DIRECTIONS 4
#define BREED_CHANCE 3
#define ESCAPE_CHANCES 10

Fox::Fox(const Point &position, World *world) : Animal(3, 7, "F", "Fox", position, world) {}

Fox::Fox(int strength, const Point &position, World *world)
        : Animal(strength, 4, "A", "Antelope", position, world) {}

bool Fox::sameSpecies(Organism *other) {
    return dynamic_cast<Fox*>(other) != nullptr;
}

Organism *Fox::reproduce(Point position) {
    return new Fox(position, world);
}

void Fox::action() {
    Organism *other;
    int x, y, tries = 0;
    // look for empty field or occupied by weaker organism
    do{
        int direction = rand() % DIRECTIONS;

        x = position.getX();
        y = position.getY();
        tries++;

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
        other = world->getBoard()[y][x];
        if (other == nullptr) break;
    } while (other->getStrength() > strength && tries < ESCAPE_CHANCES);
    if (tries == ESCAPE_CHANCES) return;

    if (other != nullptr) { // if not empty field
        if (!sameSpecies(other)) {  // and not same species
            if (other->collision(this)){ // if attacker succeeded, go to new field
                world->setBoardCell({position.getX(), position.getY()}, nullptr);
                setPosition({x, y});
                world->setBoardCell({position.getX(), position.getY()}, this);
            }
        }
        else{ // try to reproduce, if same species
            if (!(rand() % BREED_CHANCE)) breed();
        }
    }
    else{ // if empty, go to new field
        world->setBoardCell({position.getX(), position.getY()}, nullptr);
        setPosition({x, y});
        world->setBoardCell({position.getX(), position.getY()}, this);
    }
}

Fox::~Fox() {

}
