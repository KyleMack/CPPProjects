

#include <sstream>
#include <iostream>
#include <random>
#include <functional>
#include <stdlib.h>
#include "../hFiles/World.h"
#include "../hFiles/Human.h"
#include "../hFiles/Zombie.h"

// Initializes the world
//  Sets each square to an area reference
//   Sets the adjacent squares of each area
World::World() {

    this->predators = NUMBER_OF_ZOMBIES;
    this->prey = NUMBER_OF_HUMANS;

    // Initialize the grid
    for(int row = 0; row < WORLD_GRID_SIZE; row++){
        for(int col = 0; col < WORLD_GRID_SIZE; col++){
            // Set the space to a nullptr
            this->world[row][col] = new Area;

        }
    }

    // Set all Area's adjacent spaces
    for(int row = 0; row < WORLD_GRID_SIZE; row++){
        for(int col = 0; col < WORLD_GRID_SIZE; col++){

            // Get the current area
            Area& currArea = *this->world[row][col];

            // Check each of the eight edge spaces
            if(isValidSpace(row-1, col-1))
                currArea.setAdjacent(0, *this->world[row-1][col-1]);
            if(isValidSpace(row-1, col))
                currArea.setAdjacent(1, *this->world[row-1][col]);
            if(isValidSpace(row-1, col+1))
                currArea.setAdjacent(2, *this->world[row-1][col+1]);

            if(isValidSpace(row, col-1))
                currArea.setAdjacent(3, *this->world[row][col-1]);
            if(isValidSpace(row, col+1))
                currArea.setAdjacent(4, *this->world[row][col+1]);

            if(isValidSpace(row+1, col-1))
                currArea.setAdjacent(5, *this->world[row+1][col-1]);
            if(isValidSpace(row+1, col))
                currArea.setAdjacent(6, *this->world[row+1][col]);
            if(isValidSpace(row+1, col+1))
                currArea.setAdjacent(7, *this->world[row+1][col+1]);


        }
    }

}

// Returns the width const of the world
int World::getWorldSize() {
    return WORLD_GRID_SIZE;
}

// Given the coordinates, returns true if
//  the space is inside the grid
bool World::isValidSpace(int row, int col) {
    // Check if out of bounds
    if( row < 0 ||
        col < 0 ||
        row >= WORLD_GRID_SIZE ||
        col >= WORLD_GRID_SIZE)
        return false;
    else
        return true;
}

// Returns a formatted string containing the current board state
string World::getBoardString() {

    // Create stream object
    std::stringstream stream;

    // Add top border
    //stream << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+";
    stream << std::endl;

    // For each space on the grid
    for(int row = 0; row < WORLD_GRID_SIZE; row++){

        // Add first break
        stream << "|";

        for(int col = 0; col < WORLD_GRID_SIZE; col++){

            // Check if there is an organism
            if(this->world[row][col]->isOccupied())
                stream << this->world[row][col]->getOrganism().getName() << "|";
            else
                stream << "  |";
        }

        // And line end
        stream << std::endl;
    }

    // Get board state
    std::string boardState = stream.str();

    // Return the state
    return boardState;

}

// Sets random humans and zombies in the world
//  The first int is number of humans, second is number of zombies
void World::seedWorld() {

    // Create placeholders for row and col
    int row, col, count;

    // Set random seed
    srand(time(NULL));

    // Create the humans
    for(count = 0; count < NUMBER_OF_HUMANS; count++){

        // Get coords until Unoccupied space is found
        do{
            // Get random coords
            row = rand() % WORLD_GRID_SIZE;
            col = rand() % WORLD_GRID_SIZE;
        }while(this->world[row][col]->isOccupied());

        // Create new human
        Organism* newHuman = new Human;

        // Add to the world
        this->world[row][col]->setOrganism(newHuman);

    }

    // Create the zombies
    for(count = 0; count < NUMBER_OF_ZOMBIES; count ++){

        // Get coords until Unoccupied space is found
        do{
            // Get random coords
            row = rand() % WORLD_GRID_SIZE;
            col = rand() % WORLD_GRID_SIZE;
        }while(this->world[row][col]->isOccupied());

        // Create new zombie
        Organism* newZombie = new Zombie;

        // Add to the world
        this->world[row][col]->setOrganism(newZombie);

    }

}

bool World::preyExtinct() {
    return this->prey == 0;
}

bool World::predatorsExtinct() {
    return this->predators == 0;
}

// Returns the area associated with the given space
Area& World::getSpace(int row, int col) {
    return *this->world[row][col];
}

// Sets the area for a given space
void World::setSpace(int row, int col, Area &area) {
    this->world[row][col] = &area;
}

void World::cycle() {

    // Increase organism age
    ageStep();

    // Move all organisms
    moveStep();

    // Humans Recruit
    actionStep();

    // Zombies Starve
    starveStep();

    // Check for extinction
    countStep();

    // Reset all actions
    resetStep();

}

void World::ageStep() {

    // Iterate through each element in the grid
    for (int row = 0; row < WORLD_GRID_SIZE; row++) {
        for (int col = 0; col < WORLD_GRID_SIZE; col++) {

            // If there's an organism there, reset its action flag
            if(this->world[row][col]->isOccupied())
                this->world[row][col]->getOrganism().addAge();

        }
    }
}

void World::moveStep() {

    // Iterate through each element in the grid
    for(int row = 0; row < WORLD_GRID_SIZE; row++){
        for(int col = 0; col < WORLD_GRID_SIZE; col++){

            // Check if there is an organism capable of moving
            if(      this->world[row][col]->isOccupied() &&
                    !this->world[row][col]->getOrganism().hasActed())
                this->world[row][col]->getOrganism().move(*this->world[row][col]);

        }
    }

}

void World::resetStep() {

    // Iterate through each element in the grid
    for (int row = 0; row < WORLD_GRID_SIZE; row++) {
        for (int col = 0; col < WORLD_GRID_SIZE; col++) {

            // If there's an organism there, reset its action flag
            if(this->world[row][col]->isOccupied())
                this->world[row][col]->getOrganism().resetAction();

        }
    }
}

void World::starveStep() {

    // Iterate through each element in the grid
    for (int row = 0; row < WORLD_GRID_SIZE; row++) {
        for (int col = 0; col < WORLD_GRID_SIZE; col++) {

            // If there's an organism there, and it's a zombie
            if(this->world[row][col]->isOccupied() &&
               this->world[row][col]->getOrganism().getName() == ZOMBIE_NAME     ){

                // Check for starve condition
                if(((Zombie*)&this->world[row][col]->getOrganism())->getHunger() >= 3){
                    // Destroy current organism
                    delete &this->world[row][col]->getOrganism();
                    // Create new human
                    this->world[row][col]->setOrganism(new Human);
                    this->world[row][col]->getOrganism().hasActed();
                }
            }
        }
    }
}

void World::actionStep() {

    // Iterate through each element in the grid
    for (int row = 0; row < WORLD_GRID_SIZE; row++) {
        for (int col = 0; col < WORLD_GRID_SIZE; col++) {

            // Check if it's a human
            if (this->world[row][col]->isOccupied() &&
                this->world[row][col]->getOrganism().getName() == HUMAN_NAME) {

                // Recruit Step
                // If this is the humans third step
                if (this->world[row][col]->getOrganism().getAge()-1 % 3 == 0 &&
                    this->world[row][col]->getOrganism().getAge() != 0) {
                    ((Human *) &this->world[row][col]->getOrganism())->recruit(*this->world[row][col]);
                }
            }

            // Check if it's a zombie
            if (this->world[row][col]->isOccupied() &&
                this->world[row][col]->getOrganism().getName() == ZOMBIE_NAME) {

                // Infect Step
                // Check if the zombie can infect a human
                if(((Zombie*)&this->world[row][col]->getOrganism())->isInfectious()){
                    ((Zombie*)&this->world[row][col]->getOrganism())->infect(*this->world[row][col]);
                }

            }
        }
    }
}

void World::countStep() {

    // Reset the counters
    this->predators = 0;
    this->prey = 0;

    // Iterate through each element in the grid
    for (int row = 0; row < WORLD_GRID_SIZE; row++) {
        for (int col = 0; col < WORLD_GRID_SIZE; col++) {

            // Check if the cell is occupied
            if(this->world[row][col]->isOccupied()){

                // If it's a zombie
                if(this->world[row][col]->getOrganism().getName() == ZOMBIE_NAME)
                    this->predators++;
                // If it's a human
                else
                    this->prey++;

            }
        }
    }
}