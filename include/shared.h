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
#include "cleanMap.h"
#include "gameConfig.h"
#include "coordinates.h"
#include "global.h"

/// struct and class definitions


// contains properties of tft screen
struct Display {
  // pixel dimensions of tft display
  static const int16_t width = 240;
  static const int16_t height = 320;
  static const int16_t padding = 8;
  static const int16_t bgColor = ILI9341_BLACK;

  static void drawBackground(PDQ_ILI9341 * tft) {
      tft->fillScreen(bgColor);
  }
};

// contains properties for info bars at top and bottom parts of screen
struct InfoBarData {
  static const int16_t bgColor = ILI9341_BLACK;
  static const int16_t fontColor = ILI9341_WHITE;
  static const char * scoreLabel;
  static const char * livesLabel;
  static const char * pauseLabel;

  // top left corner of screen
  static const Coordinates topBarLabelPos;
  static const Coordinates topBarValuePos;
  static const Coordinates topBarPausePos;
  
  // bottom left corner of screen
  static const Coordinates bottomBarLabelPos;
  static const Coordinates bottomBarValuePos;
};

// contains properties of game map
struct DrawMap {
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

  static const int8_t dotOffset = 3; // where in the tile the dot is drawn
  static const int8_t pelletXOffset = 2; 
  static const int8_t pelletYOffset = 2; 
                                        
  static const int16_t bgColor = ILI9341_BLUE; // color of walls
  static const int16_t pathColor = ILI9341_BLACK; // color of paths, etc.
  static const int16_t dotColor = ILI9341_WHITE; // color of dot pickups
  static const int16_t pelletColor = ILI9341_WHITE; // color of power pellets

  // top left corner of the map (in pixels)
  static const int16_t mapStartX = Display::padding;
  static const int16_t mapStartY = Display::padding + DrawMap::tileSize*3;

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

  static void drawTile(PDQ_ILI9341 * tft, int8_t r, int8_t c);
};

// contains properties for ghosts
struct GhostData {
  // start Red on top of ghost house
  static const Coordinates redInitialPos;
  // the other ghosts are in the ghost house initially
  static const Coordinates blueInitialPos;
  static const Coordinates pinkInitialPos;
  static const Coordinates orangeInitialPos; 

  // ghost colors
  static const int16_t redColor = ILI9341_RED;
  static const int16_t blueColor = ILI9341_CYAN;
  static const int16_t pinkColor = ILI9341_PINK;
  static const int16_t orangeColor = ILI9341_ORANGE;
  static const int16_t panickedColor = ILI9341_LIGHTBLUE;

  // ghost house stuff
  static const int16_t ghostDoorColor = ILI9341_WHITE;
  static const int8_t  ghostDoorWidth = 2; // width in tiles
  static const int8_t  ghostDoorCol = 14; // 0-based tile position
  static const int8_t  ghostDoorRow = 16; // 0-based tile position
};

// base class for shapes that move in-game (ghosts and pac-man)
class Shape {
  public:
    Shape(Coordinates pos, int16_t size, int16_t color) {
      this->pos = pos;
      this->size = size;
      this->color = color;
      // this->velocity = {0, 0}; // begin stationary
    };

    // draw shape on touchscreen
    void drawShape(PDQ_ILI9341 * tft) {
      // draw shape in current position
      tft->fillRect(pos.x, pos.y, size, size, color);
    };

    // save old position and update current position
    void setPosition(Coordinates &newPos) {
      this->lastPos = this->pos;
      this->pos = newPos;
    }

  protected:
    Coordinates pos; // in pixels
    Coordinates lastPos; // used for redrawing "trail" left behind
    // Coordinates velocity; // in pixels
    int8_t size; // all Dynamic shapes are squares of length "size"
    int16_t color;
};

// tracks shape of player character Pac-Man
class PacManShape : public Shape {
  public:
    PacManShape() : Shape(
      // default position is centered below Ghost House
      {X_BOUND/2 * SCALE + SCALE/2, 27*SCALE}, 
      SCALE, 
      ILI9341_YELLOW) {};
};

// tracks shape of ghosts
class GhostShape : public Shape {
  public:
    // user must provide initial position and color for a ghost
    GhostShape(Coordinates pos, int16_t color) : Shape(pos, SCALE,
    color) {};
};

// Shows current game score to user
class ScoreBar {
  public:
    // draw top bar label
    static void drawLabel(PDQ_ILI9341 * tft, Coordinates pos, 
      const char * label) {
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // draw label
      tft->println(label);
    }
    
    // draw current game score
    static void drawScore(PDQ_ILI9341 * tft, Coordinates pos, int16_t score) {
      // overwrite previous value
      tft->fillRect(pos.x, pos.y, Display::width, FONT_HEIGHT, ILI9341_BLACK);

      // set cursor position and print score
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }

    // draw status message in top bar
    static void drawPause(PDQ_ILI9341 * tft, Coordinates pos, const char * text) {
        tft->setCursor(pos.x, pos.y);
        tft->print(text);
    }
};

// Shows remaining lives to user
class LivesBar {
  public:
    // draw bottom bar label
    static void drawLabel(PDQ_ILI9341 * tft, Coordinates pos, 
      const char * label) {
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // draw label
      tft->println(label);
    }
    
    // draw current game score
    static void drawLives(PDQ_ILI9341 * tft, Coordinates pos, int16_t score) {
      // overwrite previous value
      tft->fillRect(pos.x, pos.y, Display::width, FONT_HEIGHT, ILI9341_BLACK);

      // set cursor position and print score
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }
};


// Implementations

/* static */ const char * InfoBarData::scoreLabel = "SCORE";
/* static */ const char * InfoBarData::livesLabel = "LIVES";
/* static */ const char * InfoBarData::pauseLabel = "PAUSED";

/* static */ const Coordinates InfoBarData::topBarLabelPos = 
  { Display::padding, Display::padding };
/* static */ const Coordinates InfoBarData::topBarValuePos = 
  {InfoBarData::topBarLabelPos.x + Display::width/3, InfoBarData::topBarLabelPos.y};
/* static */ const Coordinates InfoBarData::topBarPausePos = 
  {InfoBarData::topBarLabelPos.x + 3*Display::width/5, InfoBarData::topBarLabelPos.y};  

/* static */ const Coordinates InfoBarData::bottomBarLabelPos = 
  { Display::padding, Display::height - Display::padding - 2*SCALE };

/* static */ const Coordinates InfoBarData::bottomBarValuePos = 
  { InfoBarData::bottomBarLabelPos.x + Display::width/3, 
    InfoBarData::bottomBarLabelPos.y};

/* static */ const Coordinates GhostData::redInitialPos = {X_BOUND/2 * SCALE + 
  SCALE/2, 15*SCALE};
/* static */ const Coordinates GhostData::blueInitialPos = {(X_BOUND/2 -2)* 
  SCALE + SCALE/2, 18*SCALE};
/* static */ const Coordinates GhostData::pinkInitialPos = {X_BOUND/2* 
  SCALE + SCALE/2, 18*SCALE};
/* static */ const Coordinates GhostData::orangeInitialPos = {(X_BOUND/2 +2)* 
  SCALE + SCALE/2, 18*SCALE};

/* static */ void DrawMap::drawPath(PDQ_ILI9341 * tft, uint16_t x, 
  uint16_t y) {
  tft->fillRect(x, y, tileSize, tileSize, pathColor);
}


/* static */ void DrawMap::drawDot(PDQ_ILI9341 * tft, uint16_t x, uint16_t y) {
  // fill tile first
  drawPath(tft, x, y);

  // draw dot on top of rectangle
  tft->fillRect(x + dotOffset, y + dotOffset, 
    dotSize, dotSize, dotColor);

}

/* static  */void DrawMap::drawPowerPellet(PDQ_ILI9341 * tft, uint16_t x, 
  uint16_t y) {
  // fill tile first
  drawPath(tft, x, y);

  // draw power pellet on top of rectangle
  tft->fillRect(x + pelletXOffset, y + pelletYOffset, 
    pelletSize, pelletSize, pelletColor);
}


/* static */ void DrawMap::drawGhostDoor(PDQ_ILI9341 * tft, uint16_t x, 
  uint16_t y) {
  tft->drawFastHLine(x, y, GhostData::ghostDoorWidth*tileSize, 
  GhostData::ghostDoorColor);
}


/* static */void DrawMap::drawTile(PDQ_ILI9341 * tft, int8_t r, 
  int8_t c) {
    switch (myMap.mapLayout[r][c]) {
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

/* static  */void DrawMap::drawMap(PDQ_ILI9341 * tft) {
  // fill background
  tft->fillRect(mapStartX, mapStartY, mapWidth*tileSize, mapHeight*tileSize, 
    bgColor);
  
  for (int8_t r = 0; r < mapHeight; ++r) {
    // left half
    for (int8_t c = 0; c < mapWidth; ++c) {
      drawTile(tft,r,c);
    }
  }

  // draw ghost door
  drawGhostDoor(tft, GhostData::ghostDoorCol*tileSize, 
    GhostData::ghostDoorRow*tileSize);
};
#endif
