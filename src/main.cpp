/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
#include <shared.h>
#include "global.h"
#include "pacMan.h"
#include "ghost.h"
#include "BFS.h"

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

PacMan pac;
Ghost test;

// update state of PacMan
// side effects: 
//   - map tiles may change if pac-man eats a pellet or dot.
//   - score may increase for same reason.
//   - remaining lives may decrease if a ghost eats pacman


void updateGhosts(){
  
}

void drawGhost(){
  Coordinates cord;
  cord.x = test.draw().pos.x*SCALE + SCALE + 2;
  cord.y = test.draw().pos.y*SCALE + 4*SCALE + 1;
  redShapeP->setPosition(cord);
  redShapeP->drawShape(&tft);
}

void updatePacMan() {
  pac.action();

  test.action();
}

void drawPacMan() {
  Coordinates cord;
  cord.x = pac.draw().pos.x*SCALE + SCALE + 2;
  cord.y = pac.draw().pos.y*SCALE + 4*SCALE + 1;
  pacShapeP->setPosition(cord);
  pacShapeP->drawShape(&tft);
}

void drawScoreBar() {
  ScoreBar::drawLabel(&tft, InfoBarData::topBarLabelPos, InfoBarData::scoreLabel);
  ScoreBar::drawScore(&tft, InfoBarData::topBarValuePos, game.getScore());
}

void drawInfoBar() {
  LivesBar::drawLabel(&tft, InfoBarData::bottomBarLabelPos, InfoBarData::livesLabel);
  LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, game.getRemainingLives());
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
  // ScoreBar::drawLabel(&tft, InfoBarData::topBarLabelPos, InfoBarData::scoreLabel);
  // ScoreBar::drawScore(&tft, InfoBarData::topBarValuePos, game.getScore());
  drawScoreBar();

  // LivesBar::drawLabel(&tft, InfoBarData::bottomBarLabelPos, InfoBarData::livesLabel);
  // LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, game.getRemainingLives());
  drawInfoBar();

  /* Global controller */
}



void update() {
  updatePacMan();
  // updateGhosts();
  // updateScore();
  // updateLives();
}

void draw() {
  drawPacMan();
  drawGhost();
  // pacShape.setPosition();
  // drawPacMan();
  // drawGhosts();
  // drawTopBar();
  // drawBottomBar();
}

void checkPauseGame() {
  if (con.buttonTriggered())
    game.pauseGame();
}

// main loop for game runtime
bool running() {
  // game is paused
  checkPauseGame();
  if (game.isPaused()) {
    // print PAUSED status message on-screen
    ScoreBar::drawPause(&tft, InfoBarData::topBarPausePos, 
      InfoBarData::pauseLabel);
    
    // wait for joystick click to resume game
    while (!con.buttonTriggered()) {}
  
    // redraw top bar
    drawScoreBar();
    game.resumeGame();
  }
  
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

    // Coordinates source = {1, 1}; 
    // Coordinates dest = {29, 26}; 
    // unsigned long start = millis();
    // Coordinates nextTile = BFS(source, dest); 
    // Serial.print("Next tile is ");
    // Serial.print(nextTile.y);
    // Serial.print(",");
    // Serial.println(nextTile.x);
    // Serial.print("time in ms: ");
    // Serial.println(millis()-start);
    Serial.end();
    return 0;
}
