#include <iostream>
#include <ctime>
#include <cstdlib>

#include "World.h"
#include "Organisms/Wolf.h"
#include "Organisms/Sheep.h"
#include "Organisms/Grass.h"
#include "Organisms/SowThistle.h"
#include "Organisms/Guarana.h"
#include "Organisms/Belladonna.h"
#include "Organisms/Hogweed.h"
#include "Organisms/Human.h"
#include "Organisms/Fox.h"
#include "Organisms/Turtle.h"
#include "Organisms/Antelope.h"


// constants
#define WIDTH 30
#define HEIGHT 30

int main() {
    std::srand(std::time(nullptr));

    World world(WIDTH, HEIGHT); // creating  default world

    if(!world.loadState()){ // if user doesn't want to load a game, put some organisms to world
        world.getSizes(); // ask user for map size
        world.addOrganism(new Wolf({0, 0}, &world));
        world.addOrganism(new Wolf({0, 1}, &world));

        world.addOrganism(new Sheep({15, 0}, &world));
        world.addOrganism(new Sheep({14, 0}, &world));

        world.addOrganism(new Fox({29, 0}, &world));
        world.addOrganism(new Fox({28, 0}, &world));

        world.addOrganism(new Turtle({0, 15}, &world));
        world.addOrganism(new Turtle({0, 14}, &world));

        world.addOrganism(new Antelope({2, 2}, &world));
        world.addOrganism(new Antelope({2, 3}, &world));

        world.addOrganism(new Grass({20, 20}, &world));

        world.addOrganism(new SowThistle({20, 0}, &world));

        world.addOrganism(new Guarana({13, 13}, &world));

        world.addOrganism(new Belladonna({8, 8}, &world));

        world.addOrganism(new Hogweed({29, 29}, &world));

        // Put controllable human to world
        char answer;
        std::cout << "Add human? [y/n]\n>";
        std::cin >> answer;
        if (answer == 'Y' || answer == 'y'){
            int x, y;
            std::cout << "Give coordinates of human:";
            std::cin >> x >> y;
            world.addOrganism(new Human({x, y}, &world));
        }
    }

    // Game is in progress until limit of rounds or user decided to end simulation
    while (world.isPlay()){
        system("cls");
        world.showMessages(); // showing logs from simulation
        world.drawWorld(); // drawing map
        world.makeTurn(); // moving and stuff
        world.saveState(); // ask for save every round
    }

    return 0;
}
