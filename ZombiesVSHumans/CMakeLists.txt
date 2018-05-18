cmake_minimum_required(VERSION 3.10)
project(ZombiesVSHumans)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZombiesVSHumans
        main.cpp

        hFiles/Area.h
        hFiles/Human.h
        hFiles/Organism.h
        hFiles/World.h
        hFiles/Zombie.h

        cppFiles/Area.cpp
        cppFiles/Human.cpp
        cppFiles/Organism.cpp
        cppFiles/World.cpp
        cppFiles/Zombie.cpp
        )