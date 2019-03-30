#include <arduino.h>
#include "controller.h"
#include "pinout.h"
Controller::Controller()
{
    pinMode(VRx, INPUT);
    pinMode(VRy, INPUT);
}