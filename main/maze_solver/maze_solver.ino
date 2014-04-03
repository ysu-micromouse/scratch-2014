int board[16][16] = {
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

// int i declared elsewhere
// int j declared elsewhere
// int direc declared elsewhere

int mazeSolver() {
  if( WallToFront() == 0 ) 
  {
    // Check if spot ahead is of lesser value
      // true move forward
  } 
  else if( WallToRight()== 0 ) 
  {
    // Check if spot to right is of lesser value
      //true move right
  } 
  else if( WallToLeft() == 0 ) 
    {
    // Check if spot to left is of lesser value
      //true move left
    } 
  else {
    //Dead end
    //increase value of current position
    //Move the mouse to the reverse
       }
  
  return board[i][j];
}

int solveMaze() {
  while (mazeSolver() != 0) {}
}