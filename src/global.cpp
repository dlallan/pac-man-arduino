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
RedGhost red;

bool touching(CoordinatesF a, CoordinatesF b)
{
    Serial.println((fabs(a.x-b.x) < 1 && fabs(a.y-b.y) < 1));
    return (fabs(a.x-b.x) < 0.5 && fabs(a.y-b.y) < 0.5);
}
// Ghost pink;