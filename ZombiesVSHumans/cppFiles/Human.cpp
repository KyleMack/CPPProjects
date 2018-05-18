


#include "../hFiles/Human.h"

Human::Human() {
    this->name = HUMAN_NAME;
    this->age = 0;
}
Human::~Human() {}

void Human::move(Area &currArea) {

    // Check spaces to make sure there is room to move
    bool emptySpace = false;

    // For the four cardinal locations
    if( currArea.hasAdjacent(N) &&
       !currArea.getAdjacent(N).isOccupied())
        emptySpace = true;

    if( currArea.hasAdjacent(E) &&
       !currArea.getAdjacent(E).isOccupied())
        emptySpace = true;

    if( currArea.hasAdjacent(S) &&
       !currArea.getAdjacent(S).isOccupied())
        emptySpace = true;

    if( currArea.hasAdjacent(W) &&
       !currArea.getAdjacent(W).isOccupied())
        emptySpace = true;


    // Return if there is no empty space to move
    if(!emptySpace){
        return;
    }

    // Pick a random spot and move
    int newSpace;

    // While an empty space is not selected
    do{
        // Select a random space
        newSpace = getRandomInt(3);
        switch(newSpace){
            case 0:
                newSpace = N;
                break;
            case 1:
                newSpace = E;
                break;
            case 2:
                newSpace = S;
                break;
            case 3:
                newSpace = W;
                break;
        }
    }while(!currArea.hasAdjacent(newSpace) ||
            currArea.getAdjacent(newSpace).isOccupied());

    // Set the new area organism to this
    currArea.getAdjacent(newSpace).setOrganism(this);

    // Remove reference to this in current area
    currArea.setOrganism(nullptr);

    // Set the acted flag to true
    this->acted = true;

}

void Human::recruit(Area &currArea) {
    // Check spaces to make sure there is room to recruit
    bool emptySpace = false;

    // For the four cardinal locations
    if( currArea.hasAdjacent(N) &&
        !currArea.getAdjacent(N).isOccupied())
        emptySpace = true;

    if( currArea.hasAdjacent(E) &&
        !currArea.getAdjacent(E).isOccupied())
        emptySpace = true;

    if( currArea.hasAdjacent(S) &&
        !currArea.getAdjacent(S).isOccupied())
        emptySpace = true;

    if( currArea.hasAdjacent(W) &&
        !currArea.getAdjacent(W).isOccupied())
        emptySpace = true;


    // Return if there is no empty space to recruit
    if(!emptySpace){
        return;
    }

    // Pick a random spot to recruit
    int newSpace;

    // While an empty space is not selected
    do{
        // Select a random space
        newSpace = getRandomInt(3);
        switch(newSpace){
            case 0:
                newSpace = N;
                break;
            case 1:
                newSpace = E;
                break;
            case 2:
                newSpace = S;
                break;
            case 3:
                newSpace = W;
                break;
        }
    }while(!currArea.hasAdjacent(newSpace) ||
           currArea.getAdjacent(newSpace).isOccupied());

    // Set the new area organism to a new Human
    currArea.getAdjacent(newSpace).setOrganism(new Human);

}