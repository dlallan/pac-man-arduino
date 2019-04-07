/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Base class for game actors (ghosts and pac-man).*/
#ifndef actor_h
#define actor_h
#include <Arduino.h>
#include "coordinates.h"

// pass this between objects in game for state comparisons
struct objectInfo {
  CoordinatesF pos;
  float speed;
  int dir;
};

// Describe properties and actions of dynamic game elements with
// instances of this class. 
class Actor {
  public:
    // default ctor
    Actor(){};
    ~Actor(){};

    // perform action in-game (e.g. movement, attack, etc.)
    void action(){};

    // pass object position (in tiles) for interrogation in-game
    objectInfo draw();

    // teleport to tile position in given direction
    void tpTo(float row, float col, int dir);

  protected:
    objectInfo obj;
    // check if actor is directly on a tile (within a margin of error)
    bool isWhole(float f);

    // get what tile value f is closest to
    int near(float f);
};

#endif