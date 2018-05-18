

#ifndef KYLESVSZOMBIES_AREA_H
#define KYLESVSZOMBIES_AREA_H

#include <vector>
#include <string>
#include "Organism.h"

class Organism;

const int TOTAL_ADJACENT = 8;
const int N = 1;
const int NE = 2;
const int E = 4;
const int SE = 7;
const int S = 6;
const int SW = 5;
const int W = 3;
const int NW = 0;

using namespace std;

class Area{

private:

    Area *adjacent[8];

    Organism* organism;

    bool acted;

public:

    Area();

    Organism& getOrganism();
    void setOrganism(Organism *organism);

    Area& getAdjacent(int space);
    void setAdjacent(int space, Area &area);

    bool hasAdjacent(int space);
    bool isOccupied();

};// end class Area

#endif //KYLESVSZOMBIES_AREA_H
