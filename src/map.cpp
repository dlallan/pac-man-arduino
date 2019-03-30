/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
// Based on Amir's Snake implementation: 
// https://github.com/Mia2b/cmput274-final-project-snake
#include "Map.h"

/* 
Functions addMark and removeMark based on this:
https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
*/
Map::Map()
{
    /* Initialize a zeros map */
    for (int i = 0; i < X_BOUND; i++)
    {
        grid[i] = 0;
    }
    mask = 1;
}

void Map::addMark(Coordinates cord)
{
    /* Will mark the input coordinate with a 1 */
    grid[cord.x] |= mask<<cord.y;
}

void Map::removeMark(Coordinates cord)
{
    /* Will set the input cooordinate to 0 */
    grid[cord.x] &= ~(mask<<cord.y);
}

bool Map::isMarked(Coordinates cord)
{
    /* Will return if the map coordinate is 0 or 1 */
    return (((grid[cord.x]>>cord.y) & 1)?true:false);
}

bool Map::isOutOfBounds(Coordinates cord)
{
    /* Will return if the input coordinates are out of the mappings range */
    return (cord.x >= X_BOUND || cord.y >= Y_BOUND);
}