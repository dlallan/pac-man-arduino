#include "ghost.h"

Ghost::Ghost(Coordinates & home) {
    this->homeTile = home;
}

void Ghost::action() {
    // // behavior determined by current mode.
    // switch(currentMode) {
    //     case Scatter:
    //         // check if home tile not
    //         break;

    //     case Chase:
    //         // go forward if not at an intersection
    //         break;
        
    //     case Frightened:
    //         break;
    // }

    // else {
    //     // otherwise, the ghost needs to determine its new direction
    //     // using pathfinding.
    //     needsNewDirection = true;
    // }
}

bool Ghost::getFrightened() {
    return currentMode == Ghost::Frightened;
}

void Ghost::setCurrentMode(int8_t mode) {
    currentMode = mode;
}

bool Ghost::isValid(int16_t row, int16_t col) {
    // ASSUMPTION: inputs are not out of bounds of mapLayout!
    int16_t tile = myMap.mapLayout[row][col];
    return (tile != 0 && tile != 4);
}

bool Ghost::atIntersection() {
    // only valid when ghost position is directly on a tile
    if (!isWhole(obj.pos.x) || !isWhole(obj.pos.y)) {
        return false;
    }

    // check surrounding tiles (ghost cannot reverse direction )
    int16_t row = obj.pos.y;
    int16_t col = obj.pos.x;
    int8_t turns = 0; // number of ways ghost can change direction
    if (obj.dir != DOWN && isValid(row-1, col)) turns++; // upper tile
    if (obj.dir != UP && isValid(row+1, col)) turns++; // lower tile
    if (obj.dir != RIGHT && isValid(row, col-1)) turns++; // left tile
    if (obj.dir != LEFT && isValid(row, col+1)) turns++; // right tile

    // ghost can always in at least one direction, so an intersection
    // is when it has two or more options
    if (turns > 2) return true;
    return false;
}
