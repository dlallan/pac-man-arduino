// source: https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/
// with modifications made by us for this project.
#include "BFS.h"
#include "global.h"
#include <Arduino.h>
#include "gameConfig.h"
#include "linked_list.h"

// A Data Structure for queue used in BFS 
struct queueNode 
{ 
    Coordinates pt;  // The cordinates of a cell 
    int dist;  // cell's distance of from the source 
};
  
// check whether given cell (row, col) is a valid 
// cell or not. 
bool isValid(int row, int col) 
{ 
    // return true if row number and column number 
    // is in range 
    return (row >= 0) && (row < Y_BOUND) && 
           (col >= 0) && (col < X_BOUND); 
} 
  
// These arrays are used to get row and column 
// numbers of 4 neighbours of a given cell 
int rowNum[] = {-1, 0, 0, 1}; 
int colNum[] = {0, 1, -1, 0};

Coordinates BFS(/* int mat[][COL], */ Coordinates src, Coordinates dest) 
{ 
    bool visited[Y_BOUND][X_BOUND]; 
    memset(visited, false, sizeof visited); 
      
    // Mark the source cell as visited 
    visited[src.x][src.y] = true;
  
    // Create a queue for BFS (we're using a linked list for this)
    LinkedList<queueNode> ll;

    // Use this grid to store previous tile in searchMap[x][y]
    Coordinates searchMap[Y_BOUND][X_BOUND]; 
      
    // Distance of source cell is 0 
    queueNode s = {src, 0}; 
    ll.insertFront(s);  // Enqueue source cell 
  
    // Do a BFS starting from source cell 
    while (ll.size() > 0) 
    { 
        queueNode curr = ll.getFirst()->item; 
        Coordinates pt = curr.pt; 
  
        // If we have reached the destination cell, 
        // we can step backwards through the search map to find
        // the next tile we need to visit.
        if (pt.x == dest.x && pt.y == dest.y) {
            int row = pt.x, col = pt.y;
            while (searchMap[row][col].x != src.x 
                || searchMap[row][col].y != src.y) {
                row = searchMap[row][col].x;
                col = searchMap[row][col].y;
                if (!isValid(row, col)) {
                    // Something went wrong. Send an impossible value.
                    return {0,0};
                }
            }
            
            return {row, col};
        }

        // Otherwise dequeue the front cell in the queue 
        // and enqueue its adjacent cells 
        ll.removeFront();

        for (int i = 0; i < 4; i++) 
        { 
            int row = pt.x + rowNum[i]; 
            int col = pt.y + colNum[i]; 
              
            // if adjacent cell is valid, has path and 
            // not visited yet, enqueue it. 
            if (isValid(row, col) && 
                (myMap.mapLayout[row][col] != MapData::wall && 
                myMap.mapLayout[row][col] != MapData::nonPlayArea) && 
                !visited[row][col])
            { 
                // save the node's coordinates in the searchMap
                searchMap[row][col] = curr.pt;

                // mark cell as visited and enqueue it 
                visited[row][col] = true; 
                queueNode Adjcell = { {row, col}, 
                                      curr.dist + 1 }; 
                ll.insertBack(Adjcell); 
            } 
        } 
    } 
    
    // ASSUME PATH IS ALWAYS REACHABLE FOR PAC-MAN
    // // Return -1 if destination cannot be reached 
    // return -1; 
    return {0, 0};
} 