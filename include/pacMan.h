/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of pac-man actor.*/
#ifndef PACMAN_H
#define PACMAN_H
#include <arduino.h>
#include "actor.h"
#include "coordinates.h"

// Pac-man state is described by an instance of this class.
class PacMan: public Actor
{
    private:
        int dirQue;
        bool isValid(int row, int col);
    public:
        // default ctor. 
        // Initializes pac-man in default position and orientation.
        PacMan();

        // Move around in the game world.
        void action();

        // State changes when pac-man has consumed a power pellet.
        // 0 when weak, 1 when start strong, 2 while waiting
        int powerful; 

        unsigned long powerTimeStart; // use with millis() for power duration
        static const unsigned long powerTimeDuration = 6000; // in milliseconds
};

#endif