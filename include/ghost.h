/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of ghosts in Pac-Man*/
#ifndef ghost_h
#define ghost_h
#include "actor.h"
#include "coordinates.h"
#include "gameConfig.h"

// movement modes for all ghosts
enum mode {
    Scatter, // separate from other ghosts
    Chase,   // hunt pac-man
    Frightened // flee from pac-man (and turn blue)
};

// describe all ghosts with this class
class Ghost : public Actor {
    public:
        // initialize ghost with position, speed, direction, and error rate
        Ghost(float row, float col, float spd, int dir,int err);
        ~Ghost() {};

        // determine next state of ghost
        virtual void action();

        // return value of panicked
        bool getFrightened();

        // set value of currentMode member
        void setCurrentMode(int m);
        int getCurrentMode() { return currentMode; }

        // check if tile is valid for ghost movement
        bool isValid(int16_t row, int16_t col);

        // checks if ghost needs to recalculate dir
        // (Rule: ghost cannot reverse direction unless changing mode.
        //  So, the ghost can only change direction if at an intersection.)
        // Returns true if at intersection
        bool atIntersection();

        // set target tile member
        void setTargetTile(Coordinates pos);

        
        Coordinates lastTile; // previous position
        Coordinates currentTile; // current position

    protected:
        // where the ghost wants to go
        Coordinates targetTile;

        // where to go in scatter mode
        Coordinates homeTile;
        // value out of 1000 determines how often the ghost makes a 
        // sub-optimal turn
        int errorChance;

        // determines movement style of ghost
        // (chase is default)
        int currentMode = Chase;
        int rowNum[4] = {-1, 0, 0, 1}; 
        int colNum[4] = {0, 1, -1, 0};

        // set ghost direction randomly
        void randomPath();

        // set direction to continue down a path (no intersection exists)
        void followPath();

        // move down the path in current direction
        void moveForward();
};

#endif