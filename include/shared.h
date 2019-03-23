/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/* Shared Objects & Global Variables */
#ifndef _SHARED_H_
#define _SHARED_H_

#include <Arduino.h>
#include <SPI.h>				            // must include this here (or else IDE can't find it)
#include <PDQ_GFX.h>		            // AF: Core graphics library
#include "PDQ_ILI9341_config.h"			// PDQ: ILI9341 pins and other setup for this sketch
#include <PDQ_ILI9341.h>		        // AF: Hardware-specific library
// contains properties of tft screen
struct display {
    // pixel dimensions of tft display
    static const int16_t width = 240;
    static const int16_t height = 320;
    static const int16_t padding = 8;
    static const int8_t tileSize = 8; // size in pixels
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
    // static const barY = display::padding + 
};

// contains properties of game map
struct mapData {
    
    static const int8_t mapWidth = 28; // map width in tiles
    static const int8_t mapHeight = 31; // map height in tiles
    
    static const int16_t bgColor = ILI9341_BLUE; // color of walls
    static const int16_t pathColor = ILI9341_BLACK; // color of paths, etc.

    // top left corner of the map (in pixels)
    static const int16_t mapStartX = display::padding;
    static const int16_t mapStartY = display::padding + display::tileSize*3;

    // 2D Array for level map (left half only)
    // 0 indicates wall
    // 1 indicates path
    // TODO: see if this array can be made static and const
    bool mapLayout[mapHeight][mapWidth/2] = { 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // top row
        {0,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
        {0,1,0,0,0,0,1,0,0,1,0,0,0,0}, 
        {0,1,0,0,0,0,1,0,0,1,0,0,0,0}, 
        {0,1,1,1,1,1,1,0,0,1,1,1,1,0}, 
        {0,0,0,0,0,0,1,0,0,0,0,0,1,0},  
        {0,0,0,0,0,0,1,0,0,0,0,0,1,0},  
        {0,0,0,0,0,0,1,0,0,1,1,1,1,1}, 
        {0,0,0,0,0,0,1,0,0,1,0,0,0,1}, // top of ghost box 
        {0,0,0,0,0,0,1,0,0,1,0,1,1,1},  
        {1,1,1,1,1,1,1,1,1,1,0,1,1,1},
        {0,0,0,0,0,0,1,0,0,1,0,1,1,1},
        {0,0,0,0,0,0,1,0,0,1,0,0,0,0}, // bottom of ghost box
        {0,0,0,0,0,0,1,0,0,1,1,1,1,1}, 
        {0,0,0,0,0,0,1,0,0,1,0,0,0,0}, 
        {0,0,0,0,0,0,1,0,0,1,0,0,0,0}, 
        {0,1,1,1,1,1,1,1,1,1,1,1,1,0}, 
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
        {0,1,0,0,0,0,1,0,0,0,0,0,1,0}, 
        {0,1,1,1,0,0,1,1,1,1,1,1,1,1}, 
        {0,0,0,1,0,0,1,0,0,1,0,0,0,0}, 
        {0,0,0,1,0,0,1,0,0,1,0,0,0,0}, 
        {0,1,1,1,1,1,1,0,0,1,1,1,1,0}, 
        {0,1,0,0,0,0,0,0,0,0,0,0,1,0}, 
        {0,1,0,0,0,0,0,0,0,0,0,0,1,0}, 
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // bottom row
    };

    // draw map foreground to tft screen
    // TODO: see if this method can be made static
    void drawMap(PDQ_ILI9341 * tft) {
        // fill background
        tft->fillRect(mapStartX, mapStartY, mapWidth*display::tileSize, mapHeight*display::tileSize, bgColor);
        for (int16_t r = 0; r < mapHeight; ++r) {
            // left half
            Serial.print("drawing row ");
            Serial.println(r);
            for (int16_t c = 0; c < mapWidth/2; ++c) {
                if (this->mapLayout[r][c]) { // draw path/foreground
                    tft->fillRect(mapStartX + c*display::tileSize, mapStartY + r*display::tileSize, 
                        display::tileSize, display::tileSize, pathColor);
                }
            }

            // right half
            for (int16_t c = mapWidth/2 - 1; c >= 0; --c) {
                if (this->mapLayout[r][c]) { // draw path/foreground
                    tft->fillRect(mapStartX + (mapWidth-c-1)*display::tileSize, mapStartY + r*display::tileSize, 
                        display::tileSize, display::tileSize, pathColor);
                }
            }
        }
    };
    
};
#endif