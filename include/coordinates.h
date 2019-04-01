/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
// Based on Amir's Snake implementation: 
// https://github.com/Mia2b/cmput274-final-project-snake
#ifndef coordinates_h
#define coordinates_h
#include <Arduino.h>

struct Coordinates
{   
    /* A structure for storing x y coordinates */
    int16_t x;
    int16_t y;
 
};

struct CoordinatesF
{   
    /* A structure for storing floating x y coordinates */
    float x;
    float y;
       inline bool operator==(CoordinatesF a) {
       if (fabs(a.x-x)<0.04 && fabs(a.y- y)<0.04)
          return true;
       else
          return false;
    }
};

#endif