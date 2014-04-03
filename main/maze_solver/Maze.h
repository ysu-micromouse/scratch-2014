#ifndef MAZE_H
#define MAZE_H

#include <Arduino.h>

struct WallMemory {
  bool N, S, E, W;
};

enum CardinalDirection {
  NORTH,
  SOUTH,
  EAST,
  WEST
};

class Maze {
public:
  Maze();
  ~Maze();
  int board[16][16];
  WallMemory boardWalls[16][16];
  int x_pos, y_pos, direc;
  
  int minNeighbor(int x, int y);
  int* minDirec(int x, int y);
  
  bool checkFinish(int x, int y);
  bool checkConsistency(int x, int y);
  
  void fixMaze();
  void decideMovement();
};

#endif
