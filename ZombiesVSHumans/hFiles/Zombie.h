
#ifndef KYLESVSZOMBIES_ZOMBIE_H
#define KYLESVSZOMBIES_ZOMBIE_H


#include "Organism.h"
#include "Area.h"

class Zombie : public Organism{

private:

    int hunger;
    int infection;

public:

    Zombie();

    int getHunger();

    void increaseInfection();
    bool isInfectious();

    virtual void move(Area& currArea);
    void infect(Area& currArea);

};

#endif //KYLESVSZOMBIES_ZOMBIE_H
