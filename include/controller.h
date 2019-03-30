#ifndef controller_h
#define controller_h

enum directions
{
    UP,
    RIGHT,
    LEFT,
    DOWN
};

class Controller
{
  private:
    int lastState;
    int currentState;
  public:
    Controller();
    int getDirection();
    int getButton();
    void update();
};

#endif