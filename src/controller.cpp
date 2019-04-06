/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of game controller*/
#include <arduino.h>
#include "controller.h"
#include "pinout.h"
#include "gameConfig.h"

Controller::Controller()
{
    pinMode(VRx, INPUT);        // x joystick
    pinMode(VRy, INPUT);        // y joystick
    pinMode(SW, INPUT_PULLUP);  // Button pin
    currentState = digitalRead(SW); // Init button state
}

int Controller::getDirection()
{
    // Read the joystick positon and make the centre (0,0)
    joyX = long(analogRead(VRx)-STICK_OFFSET);
    joyY = long(analogRead(VRy)-STICK_OFFSET);
    // Get the squared magnitude (leaving it squared so no need for sqrt)
    magnitude = (joyX*joyX + joyY*joyY);

    if (magnitude > DEAD_ZONE)
    {
        // Up 45 to 135
        // Down -45 to -135
        // Right -45 to 45
        // Left <-135 or > 135
        angle = atan2(-joyY,joyX)*(180.0/PI);
        if (angle >= 45 && angle <= 135)
        {
            return UP;
        }
        else if (angle <= -45 && angle >= -135)
        {
            return DOWN;
        }
        else if (angle <= 45 && angle >= -45)
        {
            return RIGHT;
        }
        else
        {
            return LEFT;
        }
    }
    /* else */
    return NEUTRAL;
}

bool Controller::buttonTriggered()
{
    /* Will update the button readings */
    lastState = currentState;
    currentState = digitalRead(SW);
    /* Return if the button just got pressed down */
    return (currentState == LOW && lastState == HIGH);
}