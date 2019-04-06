/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Base class for game actors (ghosts and pac-man).*/
#include "actor.h"

objectInfo Actor::draw() { 
    return obj;
}

void Actor::tpTo(float row, float col, int dir) {
    obj.dir = dir;
    obj.pos.x = col;
    obj.pos.y = row;
}

bool Actor::isWhole(float f) {
    // Check if the float is within 0.03 of a whole tile
    return (fabs(f - round(f)) < 0.03);
}

int Actor::near(float f) {
    // Get the int of the input float
    return int(round(f));
}
