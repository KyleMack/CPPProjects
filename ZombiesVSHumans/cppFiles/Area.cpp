

#include "../hFiles/Area.h"

// Initializes a new area with the organism as nullptr
Area::Area() {
    // set organism to nullptr
    this->organism = nullptr;

    // Set each adjacent space to nullptr
    for(int i = 0; i < 8; i++){
        this->adjacent[i] = nullptr;
    }
}

// Returns the currently contained organism
Organism& Area::getOrganism() {
    return *this->organism;
}

// Sets the contained organism
void Area::setOrganism(Organism *organism){
    this->organism = organism;
}

// Returns reference to an area adjacent to it on the grid
//  using the space param to determine location
//   Locations are as follows:
//       0 1 2
//       3   4
//       5 6 7
//    With the center space being the current area
Area& Area::getAdjacent(int space) {
    return *this->adjacent[space];
}

// Sets the adjacent space to a relative space on the grid
void Area::setAdjacent(int space, Area &area) {
    this->adjacent[space] = &area;
}

bool Area::hasAdjacent(int space) {
    return (this->adjacent[space] != nullptr);
}

// Returns true if the area contains an organism
bool Area::isOccupied() {
    return (this->organism != nullptr);
}
