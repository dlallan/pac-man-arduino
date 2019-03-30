/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/* Shared Objects & Global Variables */
// WARNING: PDQ library must only be included ONCE in your project to avoid
// linker errors! That's why all our PDQ-related stuff is defined here, despite
// this being a header file.
#ifndef _SHARED_H_
#define _SHARED_H_

#include <Arduino.h>
#include <SPI.h>				            // must include this here (or else IDE can't find it)
#include <PDQ_GFX.h>		            // AF: Core graphics library
#include "PDQ_ILI9341_config.h"			// PDQ: ILI9341 pins and other setup for this sketch
#include <PDQ_ILI9341.h>		        // AF: Hardware-specific library
#include "gameConfig.h"

// contains properties of tft screen
struct display {
    // pixel dimensions of tft display
    static const int16_t width = 240;
    static const int16_t height = 320;
    static const int16_t padding = 8;
    static const int16_t bgColor = ILI9341_BLACK;

    static void drawBackground(PDQ_ILI9341 * tft) {
        tft->fillScreen(bgColor);
    }
};

// infoBar shows remaining lives and high score data to player
struct infoBar {
    static const int16_t bgColor = ILI9341_BLACK;
    static const int16_t fontColor = ILI9341_WHITE;
    
    // top left corner
    static const int16_t barX = display::padding;
    static const int16_t barY = display::padding;
};

// contains properties of game map
struct mapData {
    static enum {
        wall = 0,
        dot = 1, // small item
        powerPellet = 2, // large item/powerup
        barePath = 3,
        nonPlayArea = 4 // same color as bare path (e.g. inside ghost box)
    } mapStates;

    static const int8_t mapWidth = X_BOUND; // map width in tiles
    static const int8_t mapHeight = Y_BOUND; // map height in tiles

    static const int8_t tileSize = SCALE; // size in pixels
    static const int8_t dotSize = SCALE/4; // 1/4 of tile size
    static const int8_t pelletSize = SCALE/2; // 1/2 tile size
    static const int8_t ghostDoorWidth = 2; // width in tiles
    static const int8_t ghostDoorCol = 14; // 0-based tile position
    static const int8_t ghostDoorRow = 16; // 0-based tile position

    static const int8_t dotOffset = 3; // where in the tile the dot is drawn
    static const int8_t pelletXOffset = 2; 
    static const int8_t pelletYOffset = 2; 
                                          
    static const int16_t bgColor = ILI9341_BLUE; // color of walls
    static const int16_t pathColor = ILI9341_BLACK; // color of paths, etc.
    static const int16_t dotColor = ILI9341_WHITE; // color of dot pickups
    static const int16_t pelletColor = ILI9341_WHITE; // color of power pellets
    static const int16_t ghostDoorColor = ILI9341_WHITE;

    // top left corner of the map (in pixels)
    static const int16_t mapStartX = display::padding;
    static const int16_t mapStartY = display::padding + mapData::tileSize*3;

    // 2D Array for level map (left half only)
    // uses mapStates to define initial layout
    static const uint8_t mapLayout[][mapWidth/2];

    // draw map foreground to tft screen
    static void drawMap(PDQ_ILI9341 * tft);

    // draw path or non-playable area (same color)
    static void drawPath(PDQ_ILI9341 * tft, uint16_t x, uint16_t y);
    
    // draw dot (small pickup) on tft screen
    static void drawDot(PDQ_ILI9341 * tft, uint16_t x, uint16_t y);
    
    // draw power pellet (large pickup) on tft screen
    static void drawPowerPellet(PDQ_ILI9341 * tft, uint16_t x, uint16_t y);

    // draw white "door" on ghost box
    static void drawGhostDoor(PDQ_ILI9341 * tft, uint16_t x, uint16_t y);
};


/* static */const uint8_t mapData::mapLayout[][mapWidth/2] = { 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // top row
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
    {0,2,0,4,4,0,1,0,4,4,4,0,1,0}, 
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0}, 
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0}, 
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0}, 
    {0,0,0,0,0,0,1,0,0,0,0,0,3,0},  
    {4,4,4,4,4,0,1,0,0,0,0,0,3,0},  
    {4,4,4,4,4,0,1,0,0,3,3,3,3,3}, 
    {4,4,4,4,4,0,1,0,0,3,0,0,0,4}, // top of ghost box 
    {0,0,0,0,0,0,1,0,0,3,0,4,4,4},  
    {3,3,3,3,3,3,1,3,3,3,0,4,4,4},
    {0,0,0,0,0,0,1,0,0,3,0,4,4,4},
    {4,4,4,4,4,0,1,0,0,3,0,0,0,0}, // bottom of ghost box
    {4,4,4,4,4,0,1,0,0,3,3,3,3,3}, 
    {4,4,4,4,4,0,1,0,0,3,0,0,0,0}, 
    {0,0,0,0,0,0,1,0,0,3,0,0,0,0}, 
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
    {0,2,1,1,0,0,1,1,1,1,1,1,1,1}, 
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0}, 
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0}, 
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0}, 
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0}, 
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0}, 
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // bottom row
};


/* static  */void mapData::drawPath(PDQ_ILI9341 * tft, uint16_t x, uint16_t y) {
    tft->fillRect(x, y, tileSize, tileSize, pathColor);
}


/* static */ void mapData::drawDot(PDQ_ILI9341 * tft, uint16_t x, uint16_t y) {
    // fill tile first
    drawPath(tft, x, y);

    // draw dot on top of rectangle
    tft->fillRect(x + dotOffset, y + dotOffset, 
        dotSize, dotSize, dotColor);

}

/* static  */void mapData::drawPowerPellet(PDQ_ILI9341 * tft, uint16_t x, uint16_t y) {
    // fill tile first
    drawPath(tft, x, y);

    // draw power pellet on top of rectangle
    tft->fillRect(x + pelletXOffset, y + pelletYOffset, 
        pelletSize, pelletSize, pelletColor);
}


/* static */ void mapData::drawGhostDoor(PDQ_ILI9341 * tft, uint16_t x, uint16_t y) {
    tft->drawFastHLine(x, y, ghostDoorWidth*tileSize, ghostDoorColor);
}


/* static  */void mapData::drawMap(PDQ_ILI9341 * tft) {
    // fill background
    tft->fillRect(mapStartX, mapStartY, mapWidth*tileSize, mapHeight*tileSize, bgColor);
    
    for (int8_t r = 0; r < mapHeight; ++r) {
        // left half
        for (int8_t c = 0; c < mapWidth/2; ++c) {
            switch (mapLayout[r][c]) {
                case barePath: // draw same color in both cases
                case nonPlayArea:
                    drawPath(tft, mapStartX + c*tileSize, 
                        mapStartY + r*tileSize);
                    break;

                case dot: // draw dot on tile
                    drawDot(tft, mapStartX + c*tileSize, 
                        mapStartY + r*tileSize);
                    break;

                case powerPellet: // draw power pellet on tile 
                    drawPowerPellet(tft, mapStartX + c*tileSize, 
                        mapStartY + r*tileSize);
                    break;
            }
        }

        // right half (just a reflection of left half)
        for (int8_t c = mapWidth/2 - 1; c >= 0; --c) {
            switch (mapLayout[r][c]) {
                case barePath: // draw same color in both cases
                case nonPlayArea:
                    drawPath(tft, mapStartX + 
                        (mapWidth - c - 1)*tileSize,
                        mapStartY + r*tileSize);
                    break;

                case dot: // draw dot on tile
                    drawDot(tft, mapStartX + 
                        (mapWidth - c - 1)*tileSize,
                        mapStartY + r*tileSize);
                    break;

                case powerPellet: // draw power pellet on tile 
                    drawPowerPellet(tft, mapStartX + 
                        (mapWidth - c - 1)*tileSize,
                        mapStartY + r*tileSize);
                    break;
            }
        }
    }

    // draw ghost door
    drawGhostDoor(tft, ghostDoorCol*tileSize, ghostDoorRow*tileSize);
};
#endif
