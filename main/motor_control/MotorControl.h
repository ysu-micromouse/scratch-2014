#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "StackArray.h"

class MotorControl {
  enum StackDirection {
    R_BACKWARD,
    R_TO_LEFT,
    R_TO_RIGHT
  };
  public:
    MotorControl();
    ~MotorControl();
    void moveForward();
    void moveReverse();
    void moveLeft();
    void moveRight();
    StackArray<StackDirection> stack;
};

#endif
