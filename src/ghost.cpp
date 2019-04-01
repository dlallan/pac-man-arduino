#include "ghost.h"

Ghost::Ghost()
{
    obj.pos.x = 5.0f; // Col
    obj.pos.y = 1.0f; // Row
    obj.speed = 0.25f;
    obj.dir = LEFT;
}

void Ghost::action() {
    if (atIntersection())
    {
        moveForward(); // It will need a proper choice for getting the direction
    }
    else
    {
        moveForward();
    }
}

void Ghost::moveForward() {
    if (isWhole(obj.pos.x) && isWhole(obj.pos.y))
    {
        int row = near(obj.pos.y);
        int col = near(obj.pos.x);

        if (obj.dir != UP && isValid(row + 1, col))
        {
            obj.dir = DOWN;
        }
        else if (obj.dir != DOWN && isValid(row - 1, col))
        {
            obj.dir = UP;
        }
        else if (obj.dir != LEFT && isValid(row, col + 1))
        {
            obj.dir = RIGHT;
        }
        else if (obj.dir != RIGHT && isValid(row, col - 1))
        {
            obj.dir = LEFT;
        }
    }
    switch (obj.dir)
    {
    case UP:
        obj.pos.y -= obj.speed;
        break;
    case DOWN:
        obj.pos.y += obj.speed;
        break;
    case LEFT:
        obj.pos.x -= obj.speed;
        break;
    case RIGHT:
        obj.pos.x += obj.speed;
        break;
    }
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
    int row = near(obj.pos.y);
    int col = near(obj.pos.x);
    int8_t turns = 0; // number of ways ghost can change direction
    if (isValid(row-1, col)) turns++; // upper tile
    if (isValid(row+1, col)) turns++; // lower tile
    if (isValid(row, col-1)) turns++; // left tile
    if (isValid(row, col+1)) turns++; // right tile

    // ghost can always in at least one direction, so an intersection
    // is when it has two or more options
    return (turns > 2);
}
