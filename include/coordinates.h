/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Coordinate types*/
#ifndef coordinates_h
#define coordinates_h
#include <Arduino.h>

/* A structure for storing integer x y coordinates */
struct Coordinates
{   
    int16_t x;
    int16_t y; 
};

/* A structure for storing floating-point x y coordinates */
struct CoordinatesF {   
   float x;
   float y;
   
   // return true if coords are within a 0.04 margin of error
   inline bool operator==(CoordinatesF a) {
   if (fabs(a.x-x)<0.04 && fabs(a.y- y)<0.04)
      return true;
   else
      return false;
   }

   // check if coordinates overlap within a small margin
   static bool touching(CoordinatesF a, CoordinatesF b) {
      return (fabs(a.x-b.x) < 0.5 && fabs(a.y-b.y) < 0.5);
   }
};
#endif