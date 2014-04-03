#include "Maze.h"

// Maze constructor
Maze::Maze() {

  board = {
            { 14, 13, 12, 11, 10,  9,  8,  7,  7,  8,  9, 10, 11, 12, 13, 14 },
            { 13, 12, 11, 10,  9,  8,  7,  6,  6,  7,  8,  9, 10, 11, 12, 13 },
            { 12, 11, 10,  9,  8,  7,  6,  5,  5,  6,  7,  8,  9, 10, 11, 12 },
            { 11, 10,  9,  8,  7,  6,  5,  4,  4,  5,  6,  7,  8,  9, 10, 11 },
            { 10,  9,  8,  7,  6,  5,  4,  3,  3,  4,  5,  6,  7,  8,  9, 10 },
            {  9,  8,  7,  6,  5,  4,  3,  2,  2,  3,  4,  5,  6,  7,  8,  9 },
            {  8,  7,  6,  5,  4,  3,  2,  1,  1,  2,  3,  4,  5,  6,  7,  8 },
            {  7,  6,  5,  4,  3,  2,  1,  0,  0,  1,  2,  3,  4,  5,  6,  7 },
            {  7,  6,  5,  4,  3,  2,  1,  0,  0,  1,  2,  3,  4,  5,  6,  7 },
            {  8,  7,  6,  5,  4,  3,  2,  1,  1,  2,  3,  4,  5,  6,  7,  8 },
            {  9,  8,  7,  6,  5,  4,  3,  2,  2,  3,  4,  5,  6,  7,  8,  9 },
            { 10,  9,  8,  7,  6,  5,  4,  3,  3,  4,  5,  6,  7,  8,  9, 10 },
            { 11, 10,  9,  8,  7,  6,  5,  4,  4,  5,  6,  7,  8,  9, 10, 11 },
            { 12, 11, 10,  9,  8,  7,  6,  5,  5,  6,  7,  8,  9, 10, 11, 12 },
            { 13, 12, 11, 10,  9,  8,  7,  6,  6,  7,  8,  9, 10, 11, 12, 13 },
            { 14, 13, 12, 11, 10,  9,  8,  7,  7,  8,  9, 10, 11, 12, 13, 14 }
          };
          
  for(int i=0; i<16; i++) {
    for(int j=0; j<16; j++) {
      boardWalls[i][j] = defaultWallMemory;
      if(j==0) {
        boardWalls[i][j].N = true;
      }
      if(j==15) {
        boardWalls[i][j].S = true;
      }
      if(i==0) {
        boardWalls[i][j].W = true;
      }
      if(i==15) {
        boardWalls[i][j].E = true;
      }
    }
  }
  
  int x_pos = 0;
  int y_pos = 0;
  int direc = 0;

}

Maze::minNeighbor(int x, int y) {
  int min = board[x][y];
  if(!boardWalls[x][y].N) {
    if(board[x][y-1] < min) {
      min = board[x][y-1];
    }
  }
  if(!boardWalls[x][y].S) {
    if(board[x][y+1] < min) {
      min = board[x][y+1];
    }
  }
  if(!boardWalls[x][y].W) {
    if(board[x-1][y] < min) {
      min = board[x-1][y];
    }
  }
  if(!boardWalls[x][y].E) {
    if(board[x+1][y] < min) {
      min = board[x+1][y];
    }
  }
  return min;
}

Maze::minDirec(int x, int y) {
  int[] pos = { x, y };
  //
  return pos;
}

Maze::checkFinish(int x, int y) {
  return  (x==7 && y==7) ||
          (x==8 && y==7) ||
          (x==7 && x==8) ||
          (x==8 && y==8);
}

Maze::checkConsistency(int x, int y) {
  return board[x][y] != minNeighbor(x, y) + 1;
}
