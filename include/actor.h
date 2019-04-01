#ifndef actor_h
#define actor_h
#include <arduino.h>
#include "coordinates.h"

struct objectInfo
{
  CoordinatesF pos;
  float speed;
  int dir;
};

class Actor
{
public:
  Actor(){};
  ~Actor(){};
  void action(){};
  objectInfo draw()
  { 
    return obj;
  }
  void tpTo(float row, float col, int dir)
  {
    obj.dir = dir;
    obj.pos.x = col;
    obj.pos.y = row;
  }
protected:
  objectInfo obj;
  bool isWhole(float f)
  {
    // Check if the float is with 0.03 of a whole tile
    return (fabs(f - round(f)) < 0.03);
  }
  int near(float f)
  {
    // Get the int of the input float
    return int(round(f));
  }
};

#endif