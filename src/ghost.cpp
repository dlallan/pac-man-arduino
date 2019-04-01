#include "ghost.h"
#include "global.h"
#include "BFS.h"
Ghost::Ghost()
{
    obj.pos.x = 13.5f; // Col
    obj.pos.y = 11.0f; // Row
    obj.speed = 0.1f;
    obj.dir = LEFT;
}

void Ghost::action() {
    if (atIntersection())
    {
        // get next tile from pac-man's current position
        CoordinatesF pacPosF = pac.draw().pos;
        setTargetTile({near(pacPosF.x), near(pacPosF.y)}); // row, col pair!
        
        // use BFS search to get next tile in min-path
        Coordinates myPos = {near(obj.pos.x), near(obj.pos.y)};
        // BFS uses row col pairs, so swap x and y as needed
        Coordinates nextTile = BFS({myPos.y, myPos.x}, {targetTile.y, targetTile.x});
        nextTile = {nextTile.y, nextTile.x};

        // set new direction for ghost
        if (nextTile.x > myPos.x) {
            obj.dir = RIGHT;
        }
        else if (nextTile.x < myPos.x) {
            obj.dir = LEFT;
        }
        else if (nextTile.y > myPos.y) {
            obj.dir = DOWN;
        }
        else if (nextTile.y < myPos.y) {
            obj.dir = UP;
        }
        
        // move in new direction
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

void Ghost::setTargetTile(Coordinates pos) {
    targetTile = pos;
}
