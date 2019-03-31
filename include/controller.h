#ifndef controller_h
#define controller_h

enum directions
{
    UP,
    RIGHT,
    LEFT,
    DOWN,
    NEUTRAL
};

class Controller
{
  private:
    int lastState;
    int currentState;
    long joyX;
    long joyY;
    long magnitude;
    float angle;
  public:
    Controller();
    int getDirection();
    bool buttonTriggered();
};

#endif