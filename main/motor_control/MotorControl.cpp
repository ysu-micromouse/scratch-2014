#include <Arduino.h>
#include "MotorControl.h"

void MotorControl::moveForward() {
  // Arduino code to move forward one cell.
}

void MotorControl::moveRight() {
  // Arduino code to rotate the mouse right.
  MotorControl::moveForward();
}

void MotorControl::moveLeft() {
  // Arduino code to rotate the mouse left.
  MotorControl::moveForward();
}

void MotorControl::reverse() {
  // Arduino code to back up one cell.
}
