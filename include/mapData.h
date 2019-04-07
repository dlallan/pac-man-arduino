/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of game map*/
#ifndef MAPDATA_H
#define MAPDATA_H
#include <Arduino.h>
#include "gameConfig.h"
#include "cleanMap.h"

// describe map state with an instance of this class.
struct MapData
{   
    // all tiles are one of these values
    static enum {
        wall = 0,
        dot = 1,         // small item
        powerPellet = 2, // large item/powerup
        barePath = 3,
        nonPlayArea = 4 // same color as bare path (e.g. inside ghost box)
    } mapStates;

    // initialize with a clean map layout
    MapData()
    {
        initMapLayout();
    }

    // 2D map of tiles
    uint8_t mapLayout[Y_BOUND][X_BOUND] = {};

    // set all map tiles to their default state specified by blankMap
    void initMapLayout()
    {
        for (int8_t r = 0; r < Y_BOUND; ++r)
        {
            // left half
            for (int8_t c = 0; c < X_BOUND; ++c)
            {
                mapLayout[r][c] = blankMap[r][c];
            }
        }
    }
};
#endif