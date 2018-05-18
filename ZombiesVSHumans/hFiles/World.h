
#ifndef KYLESVSZOMBIES_WORLD_H
#define KYLESVSZOMBIES_WORLD_H


#include "Area.h"

// Defines the maximum size of the grid
const int WORLD_GRID_SIZE = 20;
// Defines maximum number of humans at start
const int NUMBER_OF_HUMANS = 100;
// Defines maximum number of zombies at start
const int NUMBER_OF_ZOMBIES = 5;

class World{

private:

    Area* world[WORLD_GRID_SIZE][WORLD_GRID_SIZE];
    int predators;
    int prey;

public:

    World();

    int getWorldSize();
    bool isValidSpace(int row, int col);
    string getBoardString();

    void seedWorld();

    bool preyExtinct();
    bool predatorsExtinct();

    Area& getSpace(int row, int col);
    void setSpace(int row, int col, Area &area);

    void cycle();
    void actionStep();
    void ageStep();
    void moveStep();
    void resetStep();
    void starveStep();
    void countStep();


};// end class World



#endif //KYLESVSZOMBIES_WORLD_H
