// test speed and straightness

// Right Motor:
//    full forward: 0
//    full stop: 90
//    full reverse: 180
// Left Motor:
//    full forward: 180
//    full stop: 90
//    full reverse: 0

// 5-second forward distance/straightness test results
// right,left, forward_distance (in.), right_distance (in.)
// 1300, 1700, X,  2.0"
// 1300, 1600, X,  0.5"
// 1300, 1566, X, -5.5"
// 1300, 1590, X, -1.0"
// 1300, 1595, X, bit right
// 1300, 1594, X, untested

#include <Servo.h>
const int motor_right_pin = 12;
Servo motor_right;
const int motor_left_pin = 13;
Servo motor_left;

void setup() {
  motor_right.attach(motor_right_pin);
  motor_left.attach(motor_left_pin);
  motor_right.writeMicroseconds(1500);
  motor_left.writeMicroseconds(1500);
  delay(5000);
  motor_right.writeMicroseconds(1300);
  motor_left.writeMicroseconds(1594);
  delay(5000);
  motor_right.writeMicroseconds(1500);
  motor_left.writeMicroseconds(1500);
}

void loop() {  
  delay(1000);
}
