#include "pacMan.h"
#include "controller.h"

pacMan::pacMan()
{
    obj.pos.x = 14;
    obj.pos.y = 23;
    obj.direction = UP;
    obj.speed = 3;
    obj.progress = 0;   // No progress made towards moving to the next tile
}

void pacMan::action()
{
    //int inDir = con->getDirection();

}