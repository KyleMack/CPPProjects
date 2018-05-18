

#ifndef KYLESVSZOMBIES_ORGANISM_H
#define KYLESVSZOMBIES_ORGANISM_H

#include <string>
#include "Area.h"

class Area;

const std::string ZOMBIE_NAME = "\033[1;31m██\033[0m";
const std::string HUMAN_NAME = "\033[1;32m██\033[0m";

class Organism{

protected:
    std::string name;
    int age;
    bool acted;

public:

    Organism();
    virtual ~Organism();

    virtual void move(Area& currArea);

    virtual std::string getName();
    virtual int getAge();

    virtual void addAge();
    virtual void resetAge();

    virtual bool hasActed();
    virtual void resetAction();

    int getRandomInt(int limit);

};// end Organism class



#endif //KYLESVSZOMBIES_ORGANISM_H
