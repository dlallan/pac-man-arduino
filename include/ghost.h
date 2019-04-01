#ifndef ghost_h
#define ghost_h
#include "actor.h"
#include "coordinates.h"
#include "gameConfig.h"
#include "global.h"

class Ghost : public Actor {
    public:
        // movement modes for all ghosts
        static enum {
            Scatter, // separate from other ghosts
            Chase,   // hunt pac-man
            Frightened // flee from pac-man (and turn blue)
        } mode;

        Ghost();
        ~Ghost() {};

        // determine next state of ghost
        virtual void action();

        // return value of panicked
        bool getFrightened();

        // set value of currentMode member
        void setCurrentMode(int8_t mode);

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

    protected:
        // where the ghost wants to go
        Coordinates targetTile;

        // where to go in scatter mode
        Coordinates homeTile;

        // determines movement style of ghost
        int8_t currentMode = Ghost::Scatter;
    private:
        void moveForward();
};

#endif