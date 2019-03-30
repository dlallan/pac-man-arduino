/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
// Based on Amir's Snake implementation: 
// https://github.com/Mia2b/cmput274-final-project-snake
#ifndef Map_h
#define Map_h
#include <Arduino.h>
#include "gameConfig.h"
#include "Coordinates.h"

class Map
{
    /* A map object the allows for storing binary states of coordinates in a
    memory efficient way. */
    public:
        Map();
        void addMark(Coordinates cord);
        void removeMark(Coordinates cord);
        bool isMarked(Coordinates cord);
        bool isOutOfBounds(Coordinates cord);
    private:
        uint64_t grid[X_BOUND];
        uint64_t mask;
};

#endif