#include "Human.h"
#include <iostream>

Human::Human(const Point &position, World *world) : Animal(
        5, 4, "C", "Human", position, world) {
}

Human::Human(int strength, const Point &position, World *world) : Animal(
        strength, 4, "C", "Human", position, world) {
}

bool Human::sameSpecies(Organism *other) {
    return dynamic_cast<Human*>(other) != nullptr;
}

Organism *Human::reproduce(Point position) {
    return new Human(position, world);
}

// move to chosen field, or try to use ability
void Human::action() {
    char direction;
    std::cout << "w - north\ns - south\na - west\nd - east\nr - invincibility\n>";
    std::cin >> direction;

    int x = position.getX();
    int y = position.getY();

    switch (direction) {
        case 'w': // North
            (y > 0) ? y-- : y;
            break;
        case 's' : // South
            (y < world->getHeight() - 1) ? y++ : y;
            break;
        case 'a' : // West
            (x > 0) ? x-- : x;
            break;
        case 'd' : // East
            (x < world->getWidth() - 1) ? x++ : x;
            break;
        case 'r' : // Special ability
            if (invincibility == -5) becomeInvincible();
            else if (invincibility > 0) {
                world->addMessage(getName() + " invincibility is turned on for " + std::to_string(invincibility) + " turns. Lost move.");
            }
            else {
                world->addMessage(getName() + " invincibility is not ready for " + std::to_string(invincibility + 5) + " more rounds. Lost move.");
            }
        break;
        default:
            break;
    }
    Organism *other = world->getBoard()[y][x];
    if (other != nullptr) { // if not empty
        if (!sameSpecies(other)) { // and not same species, but I'm alone in this world anyway...
            if (other->collision(this)){ // if attacker succeeded, go to new field
                world->setBoardCell({position.getX(), position.getY()}, nullptr);
                setPosition({x, y});
                world->setBoardCell({position.getX(), position.getY()}, this);
            }
        }
    }
    else{ // if field is empty, go there
        world->setBoardCell({position.getX(), position.getY()}, nullptr);
        setPosition({x, y});
        world->setBoardCell({position.getX(), position.getY()}, this);
    }
    if (invincibility != -5){
        if (--invincibility == 0){ // decrease invincibility value every round, can be used at -5
            std::string message = getName() + " lost invincibility.";
            world->addMessage(message);
        }
    };
}

void Human::becomeInvincible() {
    std::string message = getName() + " became invincible for 5 turns.";
    world->addMessage(message);
    invincibility = 5; // set invincibility for 5 rounds
}

Human::~Human() {

}

