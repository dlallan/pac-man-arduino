/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of game controller*/
#ifndef controller_h
#define controller_h

// defines directions the player can move pac-man
enum directions
{
    UP,
    RIGHT,
    LEFT,
    DOWN,
    NEUTRAL
};

// Game controller is described by an instance of this class
class Controller
{
  public:
    // default ctor
    Controller();

    // get player action to determine current direction
    int getDirection();

    // return true if button pressed.
    // Otherwise, return false.
    bool buttonTriggered();

  private:
    // previous state of button
    int lastState;

    // current state of button
    int currentState;

    // joystick x position
    long joyX;

    // joystick y position
    long joyY;

    // sum of joyX^2 and joyY^2 (use for calculating joystick pitch)
    long magnitude;

    // current joystick pitch in degrees
    float angle;
};

#endif