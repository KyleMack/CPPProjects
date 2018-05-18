

#ifndef KYLESVSZOMBIES_HUMAN_H
#define KYLESVSZOMBIES_HUMAN_H


#include "Organism.h"
#include "Area.h"

class Human : public Organism{

private:

public:

    Human();
    ~Human();

    void move(Area &currArea);

    void recruit(Area &currArea);

};

#endif //KYLESVSZOMBIES_HUMAN_H
