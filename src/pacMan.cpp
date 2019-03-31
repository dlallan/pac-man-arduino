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

    if (isWhole(obj.pos.x) && isWhole(obj.pos.y))
    {
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
    Serial.println("X: " + String(obj.pos.x) + "Y: " + String(obj.pos.x));
}