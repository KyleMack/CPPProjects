#include <iostream>
#include <unistd.h>
#include "hFiles/Area.h"
#include "hFiles/World.h"
#include "hFiles/Human.h"
#include "hFiles/Zombie.h"

void dd(string value);
void clear();
void printGen(int generation);

int main() {

    // Define world
    World game;

    // Seed the world
    game.seedWorld();

    // Holds the current generation
    int  generation = 0;
    std::string gen = "Generation: ";

    // Introduction
    dd("Welcome to Zombies vs Kyles!");
    dd("Press any button to begin...");
    std::cin.get();

    // Run while both types are on the board
    do{

        clear();
        generation++;

        dd(game.getBoardString());
        printGen(generation);

        game.cycle();

        usleep(100000);

    }while(!game.predatorsExtinct() && !game.preyExtinct());

    clear();
    dd(game.getBoardString());
    printGen(generation);


    // Check which went extinct
    if(game.preyExtinct())
        dd("Predators Won!");
    else
        dd("Prey Won!");

    std::cin.get();
}// end Main


void dd(string value){
    std::cout << value << std::endl;
}

void clear(){
    dd("\033[H\033[J");
}

void printGen(int generation){
    std::cout << "Generation: " << generation << std::endl;
}

