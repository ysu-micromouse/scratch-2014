#include "Arduino.h"
#include "Maze.h"

// Maze constructor
Maze::Maze() {

  int temp_board[16][16] = {
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
      board[i][j] = temp_board[i][j];
    } 
  }
  WallMemory defaultWallMemory = { false, false, false, false }; 
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
  CardinalDirection direc = EAST;

}

int Maze::minNeighbor(int x, int y) {
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

int* Maze::minDirec(int x, int y) {
  int min = board[x][y];
  int min_pos[2] = {x, y};
  if(!boardWalls[x][y].N) {
    if(board[x][y-1] < min) {
      min = board[x][y-1];
      min_pos[0] = x;
      min_pos[1] = y-1;
    }
  }
  if(!boardWalls[x][y].S) {
    if(board[x][y+1] < min) {
      min = board[x][y+1];
      min_pos[0] = x;
      min_pos[1] = y+1;
    }
  }
  if(!boardWalls[x][y].W) {
    if(board[x-1][y] < min) {
      min = board[x-1][y];
      min_pos[0] = x-1;
      min_pos[1] = y;
    }
  }
  if(!boardWalls[x][y].E) {
    if(board[x+1][y] < min) {
      min = board[x+1][y];
      min_pos[0] = x+1;
      min_pos[1] = y;
    }
  }
  return min_pos;
}

bool Maze::checkFinish(int x, int y) {
  return  (x==7 && y==7) ||
          (x==8 && y==7) ||
          (x==7 && x==8) ||
          (x==8 && y==8);
}

bool Maze::checkConsistency(int x, int y) {
  return board[x][y] != minNeighbor(x, y) + 1;
}

void Maze::fixMaze() {
  int temp = 0;
  while (board[x_pos][y_pos] != temp) {
    temp = board[x_pos][y_pos];
    for(int i = 0; i < 16; i++) {
      for(int j = 0; j < 16; j++) {
        if(!checkFinish(i, j)) {
          if(!checkConsistency(i, j)) {
            board[i][j] = minNeighbor(i, j) + 1;
          }
        }
      }
    }
  }
}

void Maze::decideMovement() {
  int directionNeedToGo[2];// = minDirec(x_pos, y_pos);
  directionNeedToGo[0] = minDirec(x_pos, y_pos)[0];
  directionNeedToGo[1] = minDirec(x_pos, y_pos)[1];
  WallMemory currentWalls = boardWalls[x_pos][y_pos];
  switch (direc) {
    case EAST:
      if(!currentWalls.E) {
        if( directionNeedToGo[0] == x_pos+1 && directionNeedToGo[1] == y_pos) { //{x_pos+1, y_pos} == directionNeedToGo ) {
          MotorControl::moveForward();
          return;
        }
      }
      if(!currentWalls.W) {
        if( directionNeedToGo[0] == x_pos-1 && directionNeedToGo[1] == y_pos ) {
          MotorControl::moveReverse();
          return;
        }
      }
      if(!currentWalls.S) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos+1 ) {
          MotorControl::moveRight();
          return;
        }
      }
      if(!currentWalls.N) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos-1 ) {
          MotorControl::moveLeft();
          return;
        }
      }
      break;
    case SOUTH:
      if(!currentWalls.E) {
        if( directionNeedToGo[0] == x_pos+1 && directionNeedToGo[1] == y_pos ) {
          MotorControl::moveLeft();
          return;
        }
      }
      if(!currentWalls.W) {
        if( directionNeedToGo[0] == x_pos-1 && directionNeedToGo[1] == y_pos ) {
          MotorControl::moveRight();
          return;
        }
      }
      if(!currentWalls.S) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos+1 ) {
          MotorControl::moveForward();
          return;
        }
      }
      if(!currentWalls.N) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos-1 ) {
          MotorControl::moveReverse();
          return;
        }
      }
      break;
    case NORTH:
      if(!currentWalls.E) {
        if( directionNeedToGo[0] == x_pos+1 && directionNeedToGo[1] == y_pos ) {
          MotorControl::moveRight();
          return;
        }
      }
      if(!currentWalls.W) {
        if( directionNeedToGo[0] == x_pos-1 && directionNeedToGo[1] == y_pos ) {
          MotorControl::moveLeft();
          return;
        }
      }
      if(!currentWalls.S) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos+1 ) {
          MotorControl::moveReverse();
          return;
        }
      }
      if(!currentWalls.N) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos-1 ) {
          MotorControl::moveForward();
          return;
        }
      }
      break;
    case WEST:
      if(!currentWalls.E) {
        if( directionNeedToGo[0] == x_pos+1 && directionNeedToGo[1] == y_pos ) {
          MotorControl::moveReverse();
          return;
        }
      }
      if(!currentWalls.W) {
        if( directionNeedToGo[0] == x_pos-1 && directionNeedToGo[1] == y_pos ) {
          MotorControl::moveForward();
          return;
        }
      }
      if(!currentWalls.S) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos+1 ) {
          MotorControl::moveLeft();
          return;
        }
      }
      if(!currentWalls.N) {
        if( directionNeedToGo[0] == x_pos && directionNeedToGo[1] == y_pos-1 ) {
          MotorControl::moveRight();
          return;
        }
      }
      break;
  }
}
