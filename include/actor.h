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
  Actor();
  ~Actor();
  void action();
  objectInfo draw();

protected:
  objectInfo obj;
  bool isWhole(float f)
  {
    return (fabs(f - round(f)) < 0.04);
  }
  int near(float f)
  {
    return int(round(f));
  }
};

#endif