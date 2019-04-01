#include "ghost.h"
#include "global.h"
#include "BFS.h"
Ghost::Ghost()
{
    obj.pos.x = 13.0f; // Col
    obj.pos.y = 13.0f; // Row
    obj.speed = 0.1f;
    obj.dir = LEFT;
}

void Ghost::action() {
    // TODO: add Frightened movement behavior 
    if(isWhole(obj.pos.x) && isWhole(obj.pos.y))
    {
        lastTile = currentTile;
        currentTile.x = near(obj.pos.x);
        currentTile.y = near(obj.pos.y);
        if (atIntersection()) {
            CoordinatesF pacPosF = pac.draw().pos;
            if (currentMode == mode::Chase && !(near(pacPosF.x) == near(obj.pos.x) && near(pacPosF.y) == near(obj.pos.y) )) {
                // get next tile from pac-man's current position
                //CoordinatesF pacPosF = pac.draw().pos;
                setTargetTile({near(pacPosF.x), near(pacPosF.y)}); // row, col pair!
                
                // use BFS search to get next tile in min-path
                // Coordinates myPos = {near(obj.pos.x), near(obj.pos.y)};
                // BFS uses row col pairs, so swap x and y as needed
                Coordinates nextTile = BFS({currentTile.y, currentTile.x}, 
                    {targetTile.y, targetTile.x});
                nextTile = {nextTile.y, nextTile.x};
                // bool invalid = false;
                // set new direction for ghost

                if (nextTile.x > currentTile.x) {
                    obj.dir = RIGHT;
                //   invalid = !isValid(currentTile.y,currentTile.x+1);
                }
                else if (nextTile.x < currentTile.x) {
                    obj.dir = LEFT;
                //    invalid = !isValid(currentTile.y,currentTile.x-1);
                }
                else if (nextTile.y > currentTile.y) {
                    obj.dir = DOWN;
                //    invalid = !isValid(currentTile.y+1,currentTile.x);
                }
                else if (nextTile.y < currentTile.y) {
                    obj.dir = UP;
                //    invalid = !isValid(currentTile.y-1,currentTile.x);
                }
                // if (invalid)
                // {
                //   randomPath();
                //}
            }
            else if (currentMode == mode::Frightened) {
                // get a pseudorandom direction
                randomPath();           
            }
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
    int ran = analogRead(A7)%4;
    // Serial.println("Dir: " + String(ran));
    switch (ran)
    {
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
    return currentMode == mode::Frightened;
}

void Ghost::setCurrentMode(mode m) {
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
