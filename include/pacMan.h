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
};

#endif