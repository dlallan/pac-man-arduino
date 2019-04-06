/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Globals used throughout other game files.*/
#include "mapData.h"
#include "controller.h"
#include "game.h"
#include "pacMan.h"
#include "ghost.h"
#include <arduino.h>
Controller con;
MapData myMap;
Game game(3); // 3 lives...
PacMan pac;
Ghost red(13.0f,11.0f,0.1f,DOWN,0);        //0 -> never makes a wrong turn
Ghost pink(15.0f,16.0f,0.125f,UP,300);     // makes a wrong turn 30.0% of the time
Ghost blue(15.0f,11.0f,0.125f,RIGHT,200);  // makes a wrong turn 20.0% of the time
Ghost orange(13.0f,16.0f,0.125f,LEFT,100); // makes a wrong turn 100.0% of the time
                                           // (i.e. orange is unpredictable)
