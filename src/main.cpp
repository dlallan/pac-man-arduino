/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 1350542 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
#include <shared.h>
#include "global.h"

PDQ_ILI9341 tft; 	// AF: create LCD object (HW SPI, CS=pin 10, D/C=pin 8, reset=9)
bool run = true;


// cast of the game
PacManShape pacShape; // our hero
GhostShape redShape(GhostData::redInitialPos, GhostData::redColor);
GhostShape blueShape(GhostData::blueInitialPos, GhostData::blueColor);
GhostShape pinkShape(GhostData::pinkInitialPos, GhostData::pinkColor);
GhostShape orangeShape(GhostData::orangeInitialPos, GhostData::orangeColor);

// pointers required for polymorphism
PacManShape * pacShapeP = &pacShape; 
GhostShape * redShapeP = &redShape;
GhostShape * blueShapeP = &blueShape;
GhostShape * pinkShapeP = &pinkShape;
GhostShape * orangeShapeP = &orangeShape;

// show game over message on screen
void drawGameOver(bool winner) {
  tft.fillRect(InfoBarData::bottomBarLabelPos.x, 
    InfoBarData::bottomBarLabelPos.y, Display::width, FONT_HEIGHT, 
    ILI9341_BLACK);

  tft.setCursor(InfoBarData::bottomBarLabelPos.x, 
    InfoBarData::bottomBarLabelPos.y);
  
  if (winner) tft.print("YOU WIN!");
  else tft.print("GAME OVER");
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

// toggles ghost color if in last moments of power pellet effect duration
bool tryFrightenedToggle(GhostShape * gs) {
  if (millis() - pac.powerTimeStart >= 2*PacMan::powerTimeDuration/3) {
    gs->frightenedToggle = !gs->frightenedToggle;
    return true;
  }
  return false;
}

void drawRed(){
  Coordinates cord;
  cord.x = red.draw().pos.x*SCALE + SCALE + 2;
  cord.y = red.draw().pos.y*SCALE + 4*SCALE + 1;
  redShapeP->setPosition(cord);
  if (red.getCurrentMode() == mode::Frightened) {
    if (tryFrightenedToggle(redShapeP)) redShapeP->drawTogglingGhost(&tft);
    else redShapeP->drawPanickedGhost(&tft);
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
    if (tryFrightenedToggle(blueShapeP)) blueShapeP->drawTogglingGhost(&tft);
    else blueShapeP->drawPanickedGhost(&tft);  }
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
    if (tryFrightenedToggle(pinkShapeP)) pinkShapeP->drawTogglingGhost(&tft);
    else pinkShapeP->drawPanickedGhost(&tft);
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
    if (tryFrightenedToggle(orangeShapeP)) orangeShapeP->drawTogglingGhost(&tft);
    else orangeShapeP->drawPanickedGhost(&tft);
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

// update state of PacMan
// side effects: 
//   - map tiles may change if pac-man eats a pellet or dot.
//   - score may increase for same reason.
//   - remaining lives may decrease if a ghost eats pacman
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

// initialize or re-initialize our important variables,
// and restart game from initial state
void restart() {
  // initialize state variables
  game = Game(3);
  Controller con;
  myMap = MapData();
  pac = PacMan();
  red = Ghost(13.0f,11.0f,0.1f,DOWN,0);  //0 -> never makes a wrong turn
  pink = Ghost(15.0f,16.0f,0.125f,UP,300);   // makes a wrong turn 20.0% of the time
  blue = Ghost(15.0f,11.0f,0.125f,RIGHT,200);
  orange = Ghost(13.0f,16.0f,0.125f,LEFT,100);


  // initialize our crew
  pacShape = PacManShape(); // our hero
  redShape = GhostShape(GhostData::redInitialPos, GhostData::redColor);
  blueShape = GhostShape(GhostData::blueInitialPos, GhostData::blueColor);
  pinkShape = GhostShape(GhostData::pinkInitialPos, GhostData::pinkColor);
  orangeShape = GhostShape(GhostData::orangeInitialPos, GhostData::orangeColor);
  
  // pointers required for polymorphism
  pacShapeP = &pacShape; 
  redShapeP = &redShape;
  blueShapeP = &blueShape;
  pinkShapeP = &pinkShape;
  orangeShapeP = &orangeShape;

  tft.setTextSize(FONT_SIZE);

  // draw map
  Display::drawBackground(&tft);
  myMap.initMapLayout();
  DrawMap::drawMap(&tft);
  
  // draw everyone in their starting positions
  pacShapeP->drawShape(&tft);
  redShapeP->drawShape(&tft);
  blueShapeP->drawShape(&tft);
  pinkShapeP->drawShape(&tft);
  orangeShapeP->drawShape(&tft);
  
  // draw info bars
  drawScoreBar();
  drawLivesBar();

  delay(2000); // give the player some breathing room
}


// initialize our game variables
void setup() {
  init();               // Arduino initialization
  /* The final product doesnt need serial com's its just going to be useful 
     for debugging */
  // Serial.begin(9600);   // Start serial session at 9600 baud rate
  randomSeed(analogRead(A7)); // get new seed every time (in theory)
  tft.begin();
  restart(); // initialize game state
}

// teleport everyone home
void goHome()
{
  pac.tpTo(23.0f,14.0f,LEFT);
  red.tpTo(13.0f,11.0f,DOWN);
  pink.tpTo(15.0f,16.0f,UP);
  blue.tpTo(15.0f,11.0f,RIGHT);
  orange.tpTo(13.0f,16.0f,LEFT); 
}

// check ghost state against pac-man's state
void checkGhost(Ghost &g)
{
  // pac-man and ghost are in a fight to the death,
  // and only one can survive...
  if (touching(pac.draw().pos,g.draw().pos))
  {
    // ghost kills pac-man :(
    if (g.getCurrentMode() != mode::Frightened)
    {
      delay(Game::deathDelay); // give player time to react
      goHome();
      game.loseLife();
      game.livesChanged = true;
    }

    // pac-man kills ghost :)
    // send ghost home for a time out.
    else
    {
      g.tpTo(13.0f,12.0f,LEFT); 
      g.setCurrentMode(mode::Chase);
    }
  }
}


// check and update state of game
void update() {
  updatePacMan();
  updateGhosts();

  // compare ghost states to pac-man
  checkGhost(orange);
  checkGhost(blue);
  checkGhost(pink);
  checkGhost(red);

  // early game conditions for releasing ghosts
  //   - red is released immediately
  //   - pink is released after 20 points
  //   - blue is released after 35 points
  //   - orange is released after 50 points
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

// draw dynamic game elements
// and update UI as needed
void draw() {
  drawPacMan();
  drawGhosts();

  if (game.scoreChanged) {
    updateScore();
    game.scoreChanged = false;
  }

  if (game.livesChanged) {
    updateLives();
    game.livesChanged = false;
  }
}

// joystick click triggers pause game
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
    // print winning or losing message
    if (game.getScore() == Game::maxScore)
      drawGameOver(true);
    else  
      drawGameOver(false);
    
    // click joystick to play again
    while (!con.buttonTriggered()) {} 
    restart();
  }

  delay(FRAME_DELAY); // maintain upper bound to frame rate
  return true;
}

// program entry point
int main() {
    setup();
    while (running()); 

    // Serial.end(); // just for debugging
    return 0;
}
