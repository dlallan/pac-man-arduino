/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of pac-man actor.*/
#include "pacMan.h"
#include "global.h"

PacMan::PacMan()
{
    obj.pos.x = 14.0f;  // Col
    obj.pos.y = 23.0f;  // Row
    obj.dir = LEFT;     // Starting direction
    obj.speed = 0.125;  // Do everything wrt having things sum to 1.0 nice
    dirQue = LEFT;      // Queue up turning left (The queue can be overwritten)
}

// check that given tile is a valid area for pac-man to move
bool PacMan::isValid(int row, int col)
{
    // Check if a given row/col is a valid tile for walking on
    int tile = myMap.mapLayout[row][col];
    return (tile != MapData::wall && tile != MapData::nonPlayArea);
}

// Modifies pac-man state for movement, power-pellet consumption, or
// dot consumption.
void PacMan::action()
{
    // Process pacmans actions
    int inDir = con.getDirection(); // Read the controllers input
    float col = obj.pos.x;  // Read pacmans x/col pos
    float row = obj.pos.y;  // Read pacmans y/row pos

    if (inDir != NEUTRAL)
    {   
        // When the stick is being used get its direction
        dirQue = inDir;
    }

    if (millis() - powerTimeStart >= powerTimeDuration) {
        // Check if pacman should no longer be powerfull
        powerful = 0;
    }
    else
    {
        // Waiting for pacman to lose his power/ unable to eat ghosts
        powerful = 2;
    }
    // check if pac-man is in the centre of a tile
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
                powerful = 1;
                powerTimeStart = millis();
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
        /* Move forward/in the objects direction */
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
}