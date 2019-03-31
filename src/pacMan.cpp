#include "pacMan.h"
#include "global.h"

pacMan::pacMan()
{
    obj.pos.x = 13.5f; // Col
    obj.pos.y = 23.0f; // Row
    obj.dir = UP;
    obj.speed = 10.0 / 5.0; // Do everything wrt having things sum to 1.0 nice
    int dirQue = LEFT;
}

void pacMan::action()
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
        int tile;
        switch (dirQue)
        {
        case UP:
            tile = myMap.mapLayout[near(row) - 1][near(col)];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.dir = UP;
            }
            break;
        case DOWN:
            tile = myMap.mapLayout[near(row) + 1][near(col)];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.dir = DOWN;
            }
            break;
        case LEFT:
            tile = myMap.mapLayout[near(row)][near(col) - 1];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.dir = LEFT;
            }
            break;
        case RIGHT:
            tile = myMap.mapLayout[near(row)][near(col) + 1];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.dir = RIGHT;
            }
            break;
        }

        switch (obj.dir)
        {
        case UP:
            tile = myMap.mapLayout[near(row) - 1][near(col)];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.pos.y -= obj.speed;
            }
            break;
        case DOWN:
            tile = myMap.mapLayout[near(row) + 1][near(col)];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.pos.y += obj.speed;
            }
            break;
        case LEFT:
            tile = myMap.mapLayout[near(row)][near(col) - 1];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.pos.x -= obj.speed;
            }
            break;
        case RIGHT:
            tile = myMap.mapLayout[near(row)][near(col) + 1];
            if (tile != 0 && tile != 4) // If the space is useable
            {
                obj.pos.y += obj.speed;
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
            obj.pos.y += obj.speed;
            break;
        }
    }
}