#include "pacMan.h"
#include "global.h"
PacMan::PacMan()
{
    obj.pos.x = 13.5f; // Col
    obj.pos.y = 23.0f; // Row
    obj.dir = LEFT;
    obj.speed = 0.1; // Do everything wrt having things sum to 1.0 nice
    dirQue = LEFT;
}

bool PacMan::isValid(int row, int col)
{
    int tile = myMap.mapLayout[row][col];
    return (tile != 0 && tile != 4);
}

void PacMan::action()
{
    int inDir = con.getDirection();
    float col = obj.pos.x;
    float row = obj.pos.y;
    if (inDir != NEUTRAL)
    {
        dirQue = inDir;
    }

    // check if pac-man is on a single tile
    if (isWhole(obj.pos.x) && isWhole(obj.pos.y))
    {   
        // try moving in the requested direction
        switch (dirQue)
        {
        case UP:
            if (isValid(near(row)-1, near(col))) // If the space is useable
            {
                obj.dir = UP;
            }
            break;
        case DOWN:
            if (isValid(near(row)+1, near(col))) // If the space is useable
            {
                obj.dir = DOWN;
            }
            break;
        case LEFT:
            if (isValid(near(row), near(col)-1)) // If the space is useable
            {
                obj.dir = LEFT;
            }
            break;
        case RIGHT:
            if (isValid(near(row), near(col)+1)) // If the space is useable
            {
                obj.dir = RIGHT;
            }
            break;
        }

        // update score if pac-man has landed on a power pellet or dot
        int16_t row = near(obj.pos.y), col = near(obj.pos.x);
        int8_t tileVal = myMap.mapLayout[row][col];
        if (tileVal == MapData::dot || tileVal == MapData::powerPellet) {
            
            if (tileVal == MapData::dot)
                game.increaseScore(1);
            else {
                // TODO: increase speed temporarily and frighten ghosts
                game.increaseScore(5);
            }
            game.scoreChanged = true;
            // remove item from tile
            myMap.mapLayout[row][col] = MapData::barePath;
        }

        // move pac-man in the current direction
        switch (obj.dir)
        {
        case UP:
            if (isValid(near(row)-1, near(col))) // If the space is useable
            {
                obj.pos.y -= obj.speed;
            }
            break;
        case DOWN:
            if (isValid(near(row)+1, near(col))) // If the space is useable
            {
                obj.pos.y += obj.speed;
            }
            break;
        case LEFT:
            if (isValid(near(row), near(col)-1)) // If the space is useable
            {
                obj.pos.x -= obj.speed;
            }
            break;
        case RIGHT:
            if (isValid(near(row), near(col)+1)) // If the space is useable
            {
                obj.pos.x += obj.speed;
            }
            break;
        }
    }
    else
    {
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
    // Serial.println("X: " + String(obj.pos.x) + "Y: " + String(obj.pos.x));

    
}