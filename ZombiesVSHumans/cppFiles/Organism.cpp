
#include <iostream>
#include <random>   // for default_random_engine & uniform_int_distribution<int>
#include <chrono>   // to provide seed to the default_random_engine
#include "../hFiles/Organism.h"

Organism::Organism() {
    this->age = 0;
    this->acted = false;
}

Organism::~Organism() {

}

std::string Organism::getName() {
    return this->name;
}

int Organism::getAge() {
    return this->age;
}

void Organism::addAge() {
    this->age++;
}

void Organism::resetAge() {
    this->age = 0;
}

bool Organism::hasActed() {
    return this->acted;
}

void Organism::resetAction() {
    this->acted = false;
}

void Organism::move(Area &currArea) {

}

int Organism::getRandomInt(int limit) {
    default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uid {0,limit};   // help dre to generate nos from 0 to lim (lim included);
    return uid(dre);    // pass dre as an argument to uid to generate the random no
}