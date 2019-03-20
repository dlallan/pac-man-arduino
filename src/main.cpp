/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "shared.h"
bool run = true;

void setup()
{
  init();               // Arduino initialization
  Serial.begin(9600);   // Start serial session at 9600 baud rate
  /* The final product doesnt need serial com's its just going to be usefull 
     for debugging */
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
