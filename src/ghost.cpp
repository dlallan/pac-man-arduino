/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of ghosts in Pac-Man*/
#include "ghost.h"
#include "global.h"
#include "BFS.h"


Ghost::Ghost(float row, float col, float spd,int dir,int err)
{
    obj.pos.x = col;
    obj.pos.y = row;
    obj.speed = spd;
    obj.dir = dir;
    errorChance = err;
}

void Ghost::action() {
    // check if ghost is directly on a tile
    if(isWhole(obj.pos.x) && isWhole(obj.pos.y))
    {
        lastTile = currentTile;
        currentTile.x = near(obj.pos.x);
        currentTile.y = near(obj.pos.y);
        
        // ghost direction can change if at an intersection
        if (atIntersection()) {
            CoordinatesF pacPosF = pac.draw().pos;
            // if no error, ghost should chase pac-man
            if (random(0,1000)>errorChance && currentMode == Chase && 
                !(near(pacPosF.x) == near(obj.pos.x) && 
                near(pacPosF.y) == near(obj.pos.y) )) {
                
                // get next tile from pac-man's current position
                // (row, col pair!)
                setTargetTile({near(pacPosF.x), near(pacPosF.y)}); 
                
                // use BFS search to get next tile in min-path.
                // BFS uses row col pairs, so swap x and y as needed
                Coordinates nextTile = BFS({currentTile.y, currentTile.x}, 
                    {targetTile.y, targetTile.x});
                nextTile = {nextTile.y, nextTile.x};
                
                // set new direction for ghost (allowed to reverse direction)
                if (nextTile.x > currentTile.x) {
                    obj.dir = RIGHT;
                }
                else if (nextTile.x < currentTile.x) {
                    obj.dir = LEFT;
                }
                else if (nextTile.y > currentTile.y) {
                    obj.dir = DOWN;
                }
                else if (nextTile.y < currentTile.y) {
                    obj.dir = UP;
                }
            }
            else if (currentMode == Frightened) {
                // get a pseudorandom direction
                randomPath();           
            }
            // ghost should scatter
            else
            {
                randomPath();   
            }
        }
        else {
            // no choice but to move forward
            followPath(); 
        }
    }
    moveForward(); // keep moving to next tile in current direction
}

void Ghost::randomPath()
{
    int row = near(obj.pos.y);
    int col = near(obj.pos.x);
    
    // get random new direction
    int ran = random(0,1000)%4;
    switch (ran) {
        case UP:
            if (isValid(row - 1, col))
            {
                obj.dir = UP;
            }
            else if (isValid(row, col - 1))
            {
                obj.dir = LEFT;
            }
            else if (isValid(row + 1, col))
            {
                obj.dir = DOWN;
            }
            else if (isValid(row, col + 1))
            {
                obj.dir = RIGHT;
            }

            break;

        case DOWN:
            if (isValid(row + 1, col))
            {
                obj.dir = DOWN;
            }
            else if (isValid(row, col + 1))
            {
                obj.dir = RIGHT;
            }
            else if (isValid(row - 1, col))
            {
                obj.dir = UP;
            }
            else if (isValid(row, col - 1))
            {
                obj.dir = LEFT;
            }

            break;

        case LEFT:
            if (isValid(row, col - 1))
            {
                obj.dir = LEFT;
            }
            else if (isValid(row + 1, col))
            {
                obj.dir = DOWN;
            }
            else if (isValid(row, col + 1))
            {
                obj.dir = RIGHT;
            }
            else if (isValid(row - 1, col))
            {
                obj.dir = UP;
            }
            
            break;

        case RIGHT:
            if (isValid(row, col + 1))
            {
                obj.dir = RIGHT;
            }
            else if (isValid(row - 1, col))
            {
                obj.dir = UP;
            }
            else if (isValid(row, col - 1))
            {
                obj.dir = LEFT;
            }
            else if (isValid(row + 1, col))
            {
                obj.dir = DOWN;
            }
            
            break;
    }
}


void Ghost::followPath()
{
    // continue down path (not allowed to reverse direction)
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
    // move down path in current direction
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
    return currentMode == Frightened;
}

void Ghost::setCurrentMode(int m) {
    currentMode = m;
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

void Ghost::setTargetTile(Coordinates pos) {
    targetTile = pos;
}
