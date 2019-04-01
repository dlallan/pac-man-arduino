#ifndef ghost_h
#define ghost_h
#include "actor.h"
#include "coordinates.h"
#include "gameConfig.h"
// #include "global.h"

// movement modes for all ghosts
enum class mode {
    Scatter, // separate from other ghosts
    Chase,   // hunt pac-man
    Frightened // flee from pac-man (and turn blue)
};

class Ghost : public Actor {
    public:
        Ghost::Ghost(float row, float col, float spd,int dir,int err);
        ~Ghost() {};

        // determine next state of ghost
        virtual void action();

        // return value of panicked
        bool getFrightened();

        // set value of currentMode member
        void setCurrentMode(mode m);
        mode getCurrentMode() { return currentMode; }

        // check if tile is valid for ghost movement
        bool isValid(int16_t row, int16_t col);

        // checks if ghost needs to recalculate dir
        // (Rule: ghost cannot reverse direction unless changing mode.
        //  So, the ghost can only change direction if at an intersection.)
        // Returns true if at intersection
        bool atIntersection();

        // // set home tile member
        // void setHomeTile(Coordinates & pos);

        // set target tile member
        void setTargetTile(Coordinates pos);

        bool reDrawTile;
        Coordinates lastTile;
        Coordinates currentTile;
    protected:
        // where the ghost wants to go
        Coordinates targetTile;

        // where to go in scatter mode
        Coordinates homeTile;
        int errorChance;

        // determines movement style of ghost
        // (chase is default)
        mode currentMode = mode::Chase;
        int rowNum[4] = {-1, 0, 0, 1}; 
        int colNum[4] = {0, 1, -1, 0};
        void randomPath();
        void followPath();
        void moveForward();
};

#endif