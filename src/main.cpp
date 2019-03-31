/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
#include <shared.h>
#include "global.h"



PDQ_ILI9341 tft; 	// AF: create LCD object (HW SPI, CS=pin 10, D/C=pin 8, reset=9)
bool run = true;

// TODO: put these globals in shared.h
// They're here for testing only.
PacManShape pacShape; // our hero
PacManShape * pacShapeP = &pacShape; // pointer required for polymorphic draw
GhostShape redShape(GhostData::redInitialPos, GhostData::redColor);
GhostShape * redShapeP = &redShape;
GhostShape blueShape(GhostData::blueInitialPos, GhostData::blueColor);
GhostShape * blueShapeP = &blueShape;
GhostShape pinkShape(GhostData::pinkInitialPos, GhostData::pinkColor);
GhostShape * pinkShapeP = &pinkShape;
GhostShape orangeShape(GhostData::orangeInitialPos, GhostData::orangeColor);
GhostShape * orangeShapeP = &orangeShape;

// update state of PacMan
// side effects: 
//   - map tiles may change if pac-man eats a pellet or dot.
//   - score may increase for same reason.
//   - remaining lives may decrease if a ghost eats pacman
void updatePacMan() {
  switch(con.getDirection()) {
    case directions::UP:
    case directions::RIGHT:
    case directions::LEFT:
    case directions::DOWN:
    case directions::NEUTRAL:
      break;
  }
}

// initialize our game variables
void setup() {
  init();               // Arduino initialization
  /* The final product doesnt need serial com's its just going to be useful 
     for debugging */
  Serial.begin(9600);   // Start serial session at 9600 baud rate
  tft.begin();
  tft.setTextSize(FONT_SIZE);

  // draw map
  Display::drawBackground(&tft);
  // MapData::initMapLayout();
  DrawMap::drawMap(&tft);
  
  pacShapeP->drawShape(&tft);
  redShapeP->drawShape(&tft);
  blueShapeP->drawShape(&tft);
  pinkShapeP->drawShape(&tft);
  orangeShapeP->drawShape(&tft);
  
  // draw info bars
  ScoreBar::drawLabel(&tft, InfoBarData::topBarLabelPos, InfoBarData::scoreLabel);
  ScoreBar::drawScore(&tft, InfoBarData::topBarValuePos/* {InfoBarData::topBarPos.x + Display::width/3, 
    InfoBarData::topBarPos.y} */, 1000);

  LivesBar::drawLabel(&tft, InfoBarData::bottomBarLabelPos, InfoBarData::livesLabel);
  LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos/* { InfoBarData::bottomBarPos.x + Display::width/3, 
    InfoBarData::bottomBarPos.y} */, 3);
  
  /* Global controller */
}

void update() {
  updatePacMan();
  // updateGhosts();
  // updateScore();
  // updateLives();
}

void draw() {
  // drawPacMan();
  // drawGhosts();
  // drawTopBar();
  // drawBottomBar();
}

// main loop for game runtime
bool running() {
  // if (paused) {
  //   while (checkJoyStickClick()) {} 
  //}
  //else {
  update();
  draw();
  //}
  delay(FRAME_DELAY);
  // if (gameOver) return false;
  return true;
}

// program entry point
int main() {
    setup();
    while (running());
    Serial.end();
    return 0;
}
