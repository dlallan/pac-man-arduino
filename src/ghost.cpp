#include "ghost.h"

Ghost::Ghost()
{
    obj.pos.x = 5.0f; // Col
    obj.pos.y = 1.0f; // Row
    obj.speed = 0.25f;
    obj.dir = LEFT;
}

void Ghost::action() {
    if(isWhole(obj.pos.x) && isWhole(obj.pos.y))
    {
        lastTile = currentTile;
        currentTile.x = near(obj.pos.x);
        currentTile.y = near(obj.pos.y);
        if (atIntersection())
        {
           followPath();  // change to a new direction
        }
        else
        {
           followPath(); 
        }
    }
    moveForward();
}

void Ghost::followPath()
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

void Ghost::moveForward() {
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
