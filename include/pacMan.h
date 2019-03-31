#ifndef PACMAN_H
#define PACMAN_H
#include <arduino.h>
#include "actor.h"
#include "coordinates.h"

class pacMan: public Actor
{
    private:
        struct surounding
        {
            int left,right,up,down;
        }map;
    public:
        pacMan();
        void action();
};

#endif