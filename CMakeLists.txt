cmake_minimum_required(VERSION 3.19)
project(virtual_world)

set(CMAKE_CXX_STANDARD 14)

add_executable(virtual_world main.cpp World.cpp World.h Organism.cpp Organism.h Organisms/Plant.cpp Organisms/Plant.h Organisms/Animal.cpp Organisms/Animal.h Organisms/Wolf.cpp Organisms/Wolf.h Point.cpp Point.h Organisms/Sheep.cpp Organisms/Sheep.h Organisms/Grass.cpp Organisms/Grass.h Organisms/SowThistle.cpp Organisms/SowThistle.h Organisms/Guarana.cpp Organisms/Guarana.h Organisms/Belladonna.cpp Organisms/Belladonna.h Organisms/Hogweed.cpp Organisms/Hogweed.h Organisms/Human.cpp Organisms/Human.h Organisms/Fox.cpp Organisms/Fox.h Organisms/Turtle.cpp Organisms/Turtle.h Organisms/Antelope.cpp Organisms/Antelope.h)