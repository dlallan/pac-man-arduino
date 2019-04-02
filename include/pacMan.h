#ifndef PACMAN_H
#define PACMAN_H
#include <arduino.h>
#include "actor.h"
#include "coordinates.h"

class PacMan: public Actor
{
    private:
        int dirQue;
        bool isValid(int row, int col);
    public:
        PacMan();
        void action();
        int powerful; // 0 when weak, 1 when start strong, 2 while waiting

        unsigned long powerTimeStart; // use with millis()
        static const unsigned long powerTimeDuration = 6000; // 3 seconds
};

#endif