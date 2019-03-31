#ifndef MAPDATA_H
#define MAPDATA_H
#include <arduino.h>
#include "gameConfig.h"
#include "cleanMap.h"

struct MapData
{
    static enum {
        wall = 0,
        dot = 1,         // small item
        powerPellet = 2, // large item/powerup
        barePath = 3,
        nonPlayArea = 4 // same color as bare path (e.g. inside ghost box)
    } mapStates;
    MapData()
    {
        initMapLayout();
    }
    uint8_t mapLayout[Y_BOUND][X_BOUND] = {};

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