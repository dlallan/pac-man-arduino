/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
#include <shared.h>

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

// initialize our game variables
void setup() {
  init();               // Arduino initialization
  /* The final product doesnt need serial com's its just going to be useful 
     for debugging */
  Serial.begin(9600);   // Start serial session at 9600 baud rate
  tft.begin();
  Display::drawBackground(&tft);
  // MapData::initMapLayout();
  MapData::drawMap(&tft);
  pacShapeP->drawShape(&tft);
  redShapeP->drawShape(&tft);
  blueShapeP->drawShape(&tft);
  pinkShapeP->drawShape(&tft);
  orangeShapeP->drawShape(&tft);

  /* Global controller */
  delete con;
  con = new Controller();
}

// main loop for game runtime
bool running() {
  con->getDirection();
  con->buttonTriggered();
  return true;
}

// program entry point
int main() {
    setup();
    while (running());
    Serial.end();
    return 0;
}
