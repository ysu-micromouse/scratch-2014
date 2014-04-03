#ifndef MAZE_H
#define MAZE_H

#include <Arduino.h>

struct WallMemory {
  boolean N, S, E, W;
}
WallMemory defaultWallMemory = { false, false, false, false };

class Maze {
public:
  Maze();
  ~Maze();
  int board[16][16];
  WallMemory boardWalls[16][16];
  int x_pos, y_pos, direc;
  
  int minNeightbor(int x, int y);
  int[] minDirec(int x, int y);
  
  bool checkFinish(int x, int y);
  bool checkConsistency(int x, int y);
  
  void fixMaze();
  void decideMovement();
};

#endif
