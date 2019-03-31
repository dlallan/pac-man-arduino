#ifndef PACMAN_H
#define PACMAN_H
#include <arduino.h>
#include "actor.h"
#include "coordinates.h"

class pacMan: public Actor
{
    private:
        int dirQue;
    public:
        pacMan();
        void action();
};

#endif