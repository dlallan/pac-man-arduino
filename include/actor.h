#ifndef actor_h
#define actor_h
#include <arduino.h>
#include "coordinates.h"

struct objectInfo
{
    Coordinates pos;
    int speed;
    int progress;
    int direction;
};

class Actor {
  public:
    Actor();
    ~Actor();
    void action();
    void draw();
  protected:
    objectInfo obj;
};

#endif