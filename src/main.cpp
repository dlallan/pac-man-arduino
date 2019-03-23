/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/

// #include <Arduino.h>
// #include <SPI.h>				            // must include this here (or else IDE can't find it)
// #include <PDQ_GFX.h>		            // AF: Core graphics library
// #include "PDQ_ILI9341_config.h"			// PDQ: ILI9341 pins and other setup for this sketch
// #include <PDQ_ILI9341.h>		        // AF: Hardware-specific library
#include <shared.h>

PDQ_ILI9341 tft; 	// AF: create LCD object (HW SPI, CS=pin 10, D/C=pin 8, reset=9)
mapData m; // contains map data
bool run = true;

void setup()
{
  init();               // Arduino initialization
  /* The final product doesnt need serial com's its just going to be useful 
     for debugging */
  Serial.begin(9600);   // Start serial session at 9600 baud rate
  Serial.println("Hello World!");
  tft.begin();

  display::drawBackground(&tft);
  m.drawMap(&tft);
}

bool running()
{
  return true;
}



int main()
{
    setup();
    while (running());
    Serial.end();
    return 0;
}
