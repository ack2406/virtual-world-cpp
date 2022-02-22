#include <iostream>

#include "Organism.h"

#define MAX_TRIES 4

#define DIRECTIONS 4

Organism::Organism(int strength, int initiative, const std::string &symbol, const std::string &name, const Point &position, World *world)
        : strength(strength), initiative(initiative), symbol(symbol), name(name), position(position), world(world) {}

int Organism::getStrength() const {
    return strength;
}

void Organism::setStrength(int strength) {
    Organism::strength = strength;
}

int Organism::getInitiative() const {
    return initiative;
}

void Organism::setInitiative(int initiative) {
    Organism::initiative = initiative;
}

const Point &Organism::getPosition() const {
    return position;
}

void Organism::setPosition(const Point &position) {
    Organism::position = position;
}

World *Organism::getWorld() const {
    return world;
}

void Organism::setWorld(World *world) {
    Organism::world = world;
}

void Organism::draw() {
    std::cout << symbol;
}

// method for multiplication of organisms
// there are max tries of breeding, if no empty field was found in those tries, organisms loses chance to reproduce
void Organism::breed() {
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
    } while (world->getBoard()[dy][dx] != nullptr && tries < MAX_TRIES);
    if (tries < MAX_TRIES){ // if max tries amount was exceeded, don't reproduce
        world->addOrganism(reproduce({dx, dy}));
    }
}

std::string Organism::getName() {
    return Organism::name;
}

int Organism::getInvincibility() const {
    return invincibility;
}

void Organism::setInvincibility(int invincibility) {
    Organism::invincibility = invincibility;
}

const std::string &Organism::getSymbol() const {
    return symbol;
}

void Organism::setSymbol(const std::string &symbol) {
    Organism::symbol = symbol;
}

Organism::~Organism() {

}



