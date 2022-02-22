#include <iostream>
#include <algorithm>
#include <fstream>

#include "World.h"
#include "Organisms/Antelope.h"
#include "Organisms/Belladonna.h"
#include "Organisms/Fox.h"
#include "Organisms/Grass.h"
#include "Organisms/Guarana.h"
#include "Organisms/Hogweed.h"
#include "Organisms/Human.h"
#include "Organisms/Sheep.h"
#include "Organisms/SowThistle.h"
#include "Organisms/Turtle.h"
#include "Organisms/Wolf.h"

World::World(int width, int height) {
    this->width = width;
    this->height = height;
    for (int y = 0; y < height; y++){
        board.emplace_back();
        for (int x = 0; x < width; x++){
            board[y].push_back(nullptr); // filling board with nullpointers
        }
    }
}

void World::makeTurn() {
    sortOrganisms(); // sorting organisms before next turn
    int amount = organisms.size();
    for (int i = 0; i < amount; i++){
        if (organisms[i] != nullptr) organisms[i]->action();
    }
}

void World::drawWorld() {
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (board[y][x] == nullptr){
                std::cout << ","; // small grass if no organism on this field
            }
            else{
                board[y][x]->draw(); // drawing organism on field
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

int World::getWidth() const {
    return width;
}

int World::getHeight() const {
    return height;
}

const std::vector<std::vector<Organism *>> &World::getBoard() const {
    return board;
}

const std::vector<Organism *> &World::getOrganisms() const {
    return organisms;
}

void World::addOrganism(Organism *organism) {
    if (organism->getPosition().getX() >= 0 && organism->getPosition().getX() < width &&
        organism->getPosition().getY() >= 0 && organism->getPosition().getY() < height){
        std::string message = organism->getName() + " located on " + std::to_string(organism->getPosition().getY()) + " " +
                              std::to_string(organism->getPosition().getX()) + " was born.";
        messages.push_back(message); // adding message about newborn
        organisms.push_back(organism); // adding new organism to vector
        board[organism->getPosition().getY()][organism->getPosition().getX()] = organism; // adding new organism to field
    }
}

void World::setBoardCell(Point position, Organism *organism) {
    board[position.getY()][position.getX()] = organism; // setting chosen position to be other pointer
}

void World::popOrganism(Organism *organism) {
    std::string message = organism->getName() + " located on " + std::to_string(organism->getPosition().getY()) + " " +
            std::to_string(organism->getPosition().getX()) + " died.";
    messages.push_back(message); // adding message about dead
    setBoardCell({organism->getPosition().getX(), organism->getPosition().getY()}, nullptr); //  removing organism from field
    for (auto & i : organisms){
        if (i == organism){
            i = nullptr; // searching for organism and setting its pointer to nullptr
        }
    }
}

void World::sortOrganisms() {
    // creating new vector of organisms without dead or unsorted species
    std::vector<Organism*> newOrganisms;
    for (int initiative : initiativeList){ // looking through available initiative values and comparing to organisms
        for (Organism *organism : organisms){
            if (organism == nullptr) continue;
            if (organism->getInitiative() == initiative){
                newOrganisms.push_back(organism);
            }
        }
    }
    organisms = newOrganisms;
}

const std::vector<std::string> &World::getMessages() const {
    return messages;
}

void World::addMessage(const std::string& message) {
    messages.push_back(message);
}

void World::showMessages() {
    std::cout << "Round " << round++ << ":\n";
    for (const std::string& message : messages){
        std::cout << message << "\n";
    }
    clearMessages(); // clearing messages for new round
}

void World::clearMessages() {
    messages.clear();
}

void World::saveState() {
    char answer;
    std::cout << "Want to save the state or exit? [y/n/q]\n>";
    std::cin >> answer;

    if (answer == 'q' || answer == 'Q'){ // exit simulation
        play = false;
    }
    else if (answer == 'y' || answer == 'Y'){ // save state to file
        sortOrganisms();
        std::ofstream file("sav.txt");
        if (file.is_open()){
            file << round << " " << width << " " << height << "\n"; // saving basic configuration to first line
            for (Organism *organism : organisms){ // saving organisms stats to next lines
                file << organism->getSymbol() << " " << organism->getPosition().getX() << " " <<
                     organism->getPosition().getY() << " " << organism->getStrength() << "\n";
            }
            file.close();
        }
    }
}

bool World::loadState() {
    char answer;
    std::cout << "Load state? [y/n]\n>";
    std::cin >> answer;

    if (answer == 'y' || answer == 'Y'){ // load state from file
        std::ifstream file("sav.txt");
        if (file.is_open()){
            int newWidth, newHeight, newRound;
            file >> newRound;
            file >> newWidth;
            file >> newHeight;

            // set basic configuration of world
            setRound(newRound);
            setWidth(newWidth);
            setHeight(newHeight);

            for (int y = 0; y < height; y++){ // create new board according to loaded state
                board.emplace_back();
                for (int x = 0; x < width; x++){
                    board[y].push_back(nullptr);
                }
            }

            // load organisms
            std::string newSymbol;
            int inewPosX, inewPosY, inewStrength;
            Organism *newOrganism;

            while (file >> newSymbol){
                file >> inewPosX;
                file >> inewPosY;
                file >> inewStrength;

                // add object according to symbol of subclass

                if (newSymbol == "A"){
                    newOrganism = new Antelope(inewStrength, {inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "B"){
                    newOrganism = new Belladonna({inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "F"){
                    newOrganism = new Fox(inewStrength, {inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "/"){
                    newOrganism = new Grass({inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "G"){
                    newOrganism = new Guarana({inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "X"){
                    newOrganism = new Hogweed({inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "C"){
                    newOrganism = new Human(inewStrength, {inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "S"){
                    newOrganism = new Sheep(inewStrength, {inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "*"){
                    newOrganism = new SowThistle({inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "Z"){
                    newOrganism = new Turtle(inewStrength, {inewPosX, inewPosY}, this);
                }
                else if (newSymbol == "W"){
                    newOrganism = new Wolf(inewStrength, {inewPosX, inewPosY}, this);
                }
                else{
                    std::cout << "Error!\n";
                }

                addOrganism(newOrganism);
            }
            file.close();
        }
        return true;
    }
    return false;
}

void World::setWidth(int width) {
    World::width = width;
}

void World::setHeight(int height) {
    World::height = height;
}

int World::getRound() const {
    return round;
}

void World::setRound(int round) {
    World::round = round;
}

bool World::isPlay() const {
    return play;
}

void World::getSizes() {
    int answerX, answerY;
    std::cout << "Get Width and Height of map:";
    std::cin >> answerX >> answerY;
    setWidth(answerX);
    setHeight(answerY);
    for (int y = 0; y < height; y++){ // create new board according to user input
        board.emplace_back();
        for (int x = 0; x < width; x++){
            board[y].push_back(nullptr);
        }
    }
}

World::~World() {
    sortOrganisms();
    for (auto & organism : organisms){
        delete organism;
    }
}
