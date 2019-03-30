/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
#include <shared.h>

PDQ_ILI9341 tft; 	// AF: create LCD object (HW SPI, CS=pin 10, D/C=pin 8, reset=9)
bool run = true;
PacManShape pacShape; // our hero
PacManShape * pacShapeP = &pacShape; // pointer required for polymorphic draw

void setup()
{
  init();               // Arduino initialization
  /* The final product doesnt need serial com's its just going to be useful 
     for debugging */
  Serial.begin(9600);   // Start serial session at 9600 baud rate
  tft.begin();

  display::drawBackground(&tft);
  mapData::drawMap(&tft);
  pacShapeP->drawShape(&tft);
  /* Global controller */
  delete con;
  con = new Controller();
}

bool running()
{
  con->getDirection();
  con->buttonTriggered();
  return true;
}

int main()
{
    setup();
    while (running());
    Serial.end();
    return 0;
}
