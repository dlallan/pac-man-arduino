#ifndef GLOBAL_H
#define GLOBAL_H
#include "mapData.h"
#include "controller.h"
#include "game.h"
#include "pacMan.h"
#include "ghost.h"
#include "RedGhost.h"

extern Controller con;
extern MapData myMap;
extern Game game;
extern PacMan pac;
extern RedGhost red;
extern bool touching(CoordinatesF a, CoordinatesF b);


#endif