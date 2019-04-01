#ifndef BFS_h
#define BFS_h
#include "coordinates.h"

// Breadth-First Search implementation.
// Returns the coordinates of the next tile that the ghost should go to
// from the start tile.
// Runtime complexity: O(M*N) for an M by N matrix
Coordinates BFS(Coordinates src, Coordinates dest);
#endif