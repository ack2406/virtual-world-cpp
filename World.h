#pragma once

#include <vector>

#include "Organism.h"
class Organism;

// World is main class for simulation, which handles events like dying or adding organisms to board
class World {
    int width;
    int height;
    std::vector<Organism*> organisms; // vector for list of all alive organisms
    std::vector<std::vector<Organism*>> board; // vector 2D for displaying organisms in the world
    std::vector<std::string> messages; // vector for messages, which will be displayed at the beginning of round
    int round = 1;
    bool play = true;
public:
    World(int width, int height);

    const int initiativeList[5] = {7, 5, 4, 1, 0}; // array of available initiatives

    // getters and setters
    int getWidth() const;

    int getHeight() const;

    void setWidth(int width);

    void setHeight(int height);

    bool isPlay() const;

    const std::vector<Organism *> &getOrganisms() const;

    const std::vector<std::vector<Organism *>> &getBoard() const;

    void setBoardCell(Point position, Organism *organism);

    const std::vector<std::string> &getMessages() const;

    void addMessage(const std::string& message);

    int getRound() const;

    void setRound(int round);

    void showMessages();

    void clearMessages();

    // death of organism D:
    void popOrganism(Organism *organism);

    void makeTurn();

    void drawWorld();

    void addOrganism(Organism *organism);

    // clearing vector from dead organisms and sorting by initiative
    void sortOrganisms();

    // methods for saving and loading game from file
    void saveState();

    bool loadState();

    void getSizes();

    ~World();
};