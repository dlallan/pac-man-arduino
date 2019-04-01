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

// PacMan pac;
// Ghost red;

// update state of PacMan
// side effects: 
//   - map tiles may change if pac-man eats a pellet or dot.
//   - score may increase for same reason.
//   - remaining lives may decrease if a ghost eats pacman


// show game over message on screen
void drawGameOver() {
  tft.fillRect(InfoBarData::bottomBarLabelPos.x, 
    InfoBarData::bottomBarLabelPos.y, Display::width, FONT_HEIGHT, 
    ILI9341_BLACK);

  tft.setCursor(InfoBarData::bottomBarLabelPos.x, 
    InfoBarData::bottomBarLabelPos.y);
  
  tft.print("GAME OVER");
}

// update score display
void updateScore() {
  ScoreBar::drawScore(&tft, InfoBarData::topBarValuePos, game.getScore());
}

void updateLives() {
  LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, game.getRemainingLives());
}

void runGhost(Ghost &g)
{
  if (pac.powerful == 1) {
    g.setCurrentMode(mode::Frightened);
  }
  else if (pac.powerful == 0 && g.getCurrentMode() != mode::Chase) {
    g.setCurrentMode(mode::Chase);
  }
  g.action();
}

// update state of the four ghosts
void updateGhosts(){
  // check if pac-man state has changed
  runGhost(red);
  runGhost(pink);
  runGhost(blue);
  runGhost(orange);
}

void drawRed(){
  Coordinates cord;
  cord.x = red.draw().pos.x*SCALE + SCALE + 2;
  cord.y = red.draw().pos.y*SCALE + 4*SCALE + 1;
  redShapeP->setPosition(cord);
  if (red.getCurrentMode() == mode::Frightened) {
    redShapeP->drawPanickedGhost(&tft);
  }
  else {
    redShapeP->drawShape(&tft);
  }
  int c = red.lastTile.x;
  int r = red.lastTile.y;
  int t = myMap.mapLayout[r][c];
  if (t == 1)
  {
    DrawMap::drawDot(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
  else if (t == 2)
  {
    DrawMap::drawPowerPellet(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
}

void drawBlue(){
  Coordinates cord;
  cord.x = blue.draw().pos.x*SCALE + SCALE + 2;
  cord.y = blue.draw().pos.y*SCALE + 4*SCALE + 1;
  blueShapeP->setPosition(cord);
  if (blue.getCurrentMode() == mode::Frightened) {
    blueShapeP->drawPanickedGhost(&tft);
  }
  else {
    blueShapeP->drawShape(&tft);
  }
  int c = blue.lastTile.x;
  int r = blue.lastTile.y;
  int t = myMap.mapLayout[r][c];
  if (t == 1)
  {
    DrawMap::drawDot(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
  else if (t == 2)
  {
    DrawMap::drawPowerPellet(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
}

void drawPink(){
  Coordinates cord;
  cord.x = pink.draw().pos.x*SCALE + SCALE + 2;
  cord.y = pink.draw().pos.y*SCALE + 4*SCALE + 1;
  pinkShapeP->setPosition(cord);
  if (pink.getCurrentMode() == mode::Frightened) {
    pinkShapeP->drawPanickedGhost(&tft);
  }
  else {
    pinkShapeP->drawShape(&tft);
  }
  int c = pink.lastTile.x;
  int r = pink.lastTile.y;
  int t = myMap.mapLayout[r][c];
  if (t == 1)
  {
    DrawMap::drawDot(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
  else if (t == 2)
  {
    DrawMap::drawPowerPellet(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
}

void drawOrange(){
  Coordinates cord;
  cord.x = orange.draw().pos.x*SCALE + SCALE + 2;
  cord.y = orange.draw().pos.y*SCALE + 4*SCALE + 1;
  orangeShapeP->setPosition(cord);
  if (orange.getCurrentMode() == mode::Frightened) {
    orangeShapeP->drawPanickedGhost(&tft);
  }
  else {
    orangeShapeP->drawShape(&tft);
  }
  int c = orange.lastTile.x;
  int r = orange.lastTile.y;
  int t = myMap.mapLayout[r][c];
  if (t == 1)
  {
    DrawMap::drawDot(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
  else if (t == 2)
  {
    DrawMap::drawPowerPellet(&tft, DrawMap::mapStartX + c*DrawMap::tileSize, 
              DrawMap::mapStartY + r*DrawMap::tileSize);
  }
}

void drawGhosts() {
  drawRed();
  drawBlue();
  drawPink();
  drawOrange();
}
void updatePacMan() {
  pac.action();
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

void drawLivesBar() {
  LivesBar::drawLabel(&tft, InfoBarData::bottomBarLabelPos, InfoBarData::livesLabel);
  LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, game.getRemainingLives());
}

// initialize our game variables
void setup() {
  init();               // Arduino initialization
  /* The final product doesnt need serial com's its just going to be useful 
     for debugging */
  Serial.begin(9600);   // Start serial session at 9600 baud rate
  randomSeed(analogRead(A7));

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
  drawLivesBar();

  /* Global controller */
}


void goHome()
{
  pac.tpTo(23.0f,13.5f,LEFT);
  red.tpTo(13.0f,11.0f,DOWN);
  pink.tpTo(15.0f,16.0f,UP);
  blue.tpTo(15.0f,11.0f,RIGHT);
  orange.tpTo(13.0f,16.0f,LEFT); 
}
void checkGhost(Ghost &g)
{
  if (touching(pac.draw().pos,g.draw().pos))
  {
    if (g.getCurrentMode() != mode::Frightened)
    {
      delay(500);
      goHome();
      game.loseLife();
      game.livesChanged = true;
    }
    else
    {
      g.tpTo(11.0f,13.0f,LEFT); 
      g.setCurrentMode(mode::Chase);
    }
  }
}



void update() {
  updatePacMan();
  updateGhosts();

  checkGhost(orange);
  checkGhost(blue);
  checkGhost(pink);
  checkGhost(red);

  if (game.scoreChanged) {
    updateScore();
    game.scoreChanged = false;
  }

  if (game.livesChanged) {
    updateLives();
    game.livesChanged = false;
  }

  if(game.getScore()>20 && pink.draw().pos == CoordinatesF({13.0f,13.0f}))
  {
    pink.tpTo(11.0f,13.0f,LEFT);
  }
  else if (game.getScore()>35 && blue.draw().pos == CoordinatesF({13.0f,13.0f}))
  {
    blue.tpTo(11.0f,13.0f,LEFT);
  }
  else if (game.getScore()>50 && orange.draw().pos == CoordinatesF({13.0f,13.0f}))
  {
    orange.tpTo(11.0f,13.0f,LEFT);
  }
  else if (red.draw().pos ==  CoordinatesF({13.0f,13.0f}))
  {
    red.tpTo(11.0F,13.0f,LEFT);
  }

}

void draw() {
  drawPacMan();
  drawGhosts();

  // draw new score if needed
  // drawTopBar();

  // draw remaining lives if needed
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

  // check for game over
  if (game.isGameOver()) {
    drawGameOver();
    while (true) {} // restart arduino to play again
  }

  delay(FRAME_DELAY);
  return true;
}

// program entry point
int main() {
    setup();
    while (running()); 

    Serial.end();
    return 0;
}
