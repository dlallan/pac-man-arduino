// source: https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/
// Runtime complexity: O(M*N) for an M by N matrix
#include <Arduino.h>
#include "coordinates.h"
#include "gameConfig.h"
#include "linked_list.h"

#define ROW Y_BOUND
#define COL X_BOUND

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
int colNum[] = {0, -1, 1, 0};

// function to find the shortest path between 
// a given source cell to a destination cell. 
int BFS(int mat[][COL], Coordinates src, Coordinates dest) 
{ 
    // check source and destination cell 
    // of the matrix have value 1 
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y]) 
        return -1; 
  
    bool visited[ROW][COL]; 
    memset(visited, false, sizeof visited); 
      
    // Mark the source cell as visited 
    visited[src.x][src.y] = true; 
  
    // Create a queue for BFS 
    LinkedList<queueNode> ll; 
      
    // Distance of source cell is 0 
    queueNode s = {src, 0}; 
    ll.insertFront(s);  // Enqueue source cell 
  
    // Do a BFS starting from source cell 
    while (ll.size() > 0) 
    { 
        queueNode curr = ll.getFirst()->item; 
        Coordinates pt = curr.pt; 
  
        // If we have reached the destination cell, 
        // we are done 
        if (pt.x == dest.x && pt.y == dest.y) 
            return curr.dist; 
  
        // Otherwise dequeue the front cell in the queue 
        // and enqueue its adjacent cells 
        ll.removeBack();
  
        for (int i = 0; i < 4; i++) 
        { 
            int row = pt.x + rowNum[i]; 
            int col = pt.y + colNum[i]; 
              
            // if adjacent cell is valid, has path and 
            // not visited yet, enqueue it. 
            if (isValid(row, col) && mat[row][col] &&  
               !visited[row][col]) 
            { 
                // mark cell as visited and enqueue it 
                visited[row][col] = true; 
                queueNode Adjcell = { {row, col}, 
                                      curr.dist + 1 }; 
                ll.insertBack(Adjcell); 
            } 
        } 
    } 
  
    // Return -1 if destination cannot be reached 
    return -1; 
} 