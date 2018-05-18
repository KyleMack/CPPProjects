

#include <random>
#include <algorithm>
#include "../hFiles/Zombie.h"

Zombie::Zombie() {
    this->name = ZOMBIE_NAME;
    this->hunger = 0;
    this->age = 0;
    this->infection = 0;
}

int Zombie::getHunger() {
    return this->hunger;
}

void Zombie::increaseInfection() {
    this->infection++;
}

bool Zombie::isInfectious() {
    return (this->infection >= 8);
}

void Zombie::move(Area &currArea) {

    // Check spaces to make sure there is room to move
    bool emptySpace = false;
    int newSpace;
    std::vector<int> humans;

    // Check each of the eight locations
    for(int location = 0; location < TOTAL_ADJACENT; location++){

        // Check if there's a human
        if(currArea.hasAdjacent(location) &&
           currArea.getAdjacent(location).isOccupied() &&
           currArea.getAdjacent(location).getOrganism().getName() == HUMAN_NAME )
            // Add location to the array
            humans.push_back(location);

        // For the four cardinal locations
        if( currArea.hasAdjacent(location) &&
           !currArea.getAdjacent(location).isOccupied())
            emptySpace = true;
    }

    // Check if there are any adjacent humans
    // If there are humans
    if(!humans.empty()){

        // Create shuffle engine
        auto rng = std::default_random_engine {};

        // Shuffle the array
        std::shuffle(humans.begin(), humans.end(), rng);

        // Get random human
        newSpace = humans[0];

        // Reset hunger
        this->hunger = 0;
        this->increaseInfection();

    // If there arn't any humans
    } else {
        // Return if there is no empty space to move
        if(!emptySpace)
            return;

        // Pick a random spot and move
        newSpace;

        // While an empty space is not selected
        do{
            // Select a random space
            newSpace = getRandomInt(7);
        }while(!currArea.hasAdjacent(newSpace) ||
               currArea.getAdjacent(newSpace).isOccupied());
    }

    // Set the new area organism to this
    currArea.getAdjacent(newSpace).setOrganism(this);

    // Remove reference to this in current area
    currArea.setOrganism(nullptr);

    // Set the acted flag to true
    this->acted = true;

    // Increase the zombies hunger
    this->hunger++;
    this->increaseInfection();
}

void Zombie::infect(Area &currArea) {

    // Check spaces to make sure there is room to move
    int newSpace;
    std::vector<int> humans;

    // Check each of the eight locations
    for(int location = 0; location < TOTAL_ADJACENT; location++){

        // Check if there's a human
        if(currArea.hasAdjacent(location) &&
           currArea.getAdjacent(location).isOccupied() &&
           currArea.getAdjacent(location).getOrganism().getName() == HUMAN_NAME )
            // Add location to the array
            humans.push_back(location);
    }

    // Check if there are any adjacent humans
    // If there are humans
    if(!humans.empty()){

        // Shuffle the array
        std::random_shuffle(humans.begin(), humans.end());

        // Get random human
        newSpace = humans[0];

        // Destroy the current organism
        delete &currArea.getAdjacent(newSpace).getOrganism();

        // Create a new zombie
        currArea.getAdjacent(newSpace).setOrganism(new Zombie);

        // Reset infection
        this->infection = 0;

        // If there arn't any humans
    } else {
        return;
    }
}