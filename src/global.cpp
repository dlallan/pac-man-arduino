#include "mapData.h"
#include "controller.h"
#include "game.h"
#include "pacMan.h"
#include "ghost.h"
#include "RedGhost.h"
#include <arduino.h>
Controller con;
MapData myMap;
Game game;
PacMan pac;
Ghost red(13.0f,11.0f,0.1f,DOWN,0);  //0 -> never makes a wrong turn
Ghost pink(15.0f,16.0f,0.125f,UP,300);   // makes a wrong turn 20.0% of the time
Ghost blue(15.0f,11.0f,0.125f,RIGHT,200);
Ghost orange(13.0f,16.0f,0.125f,LEFT,100);

bool touching(CoordinatesF a, CoordinatesF b)
{
    Serial.println((fabs(a.x-b.x) < 1 && fabs(a.y-b.y) < 1));
    return (fabs(a.x-b.x) < 0.5 && fabs(a.y-b.y) < 0.5);
}
// Ghost pink;