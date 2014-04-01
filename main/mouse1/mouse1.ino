//YSU Micromouse
//Scratch 2014

#include <Servo.h>

// INPUTS
const int fSensPin = A0; // front sensor pin
const int rSensPin = A1; // right sensor pin
const int lSensPin = A2; // left sensor pin
const int rMotorPin = 12; // right motor pin
const int lMotorPin = 13; // left motor pin

// VARIABLES
float fDist = 0; // front distance (cm)
float rDist = 0; // left distance (cm)
float lDist = 0; // right distance (cm)
Servo motor_right; // right servo object
Servo motor_left; // left servo object


void setup(){
  // Set analog reference to 1.1V (integer value of 2)
  analogReference(2);
}


void loop(){
  
  // READ WALL SENSORS
  lDist = 10.174*exp(-0.006*analogRead(lSensPin));
  fDist = 10.174*exp(-0.006*analogRead(fSensPin));
  rDist = 10.174*exp(-0.006*analogRead(rSensPin));
  
  // HANDLE EVENTS HERE
  // 1. stop at wall
  // 2. adjust for straightness
  // 3. update map
  
  // HANDLE PROCESS COMPLETION HERE
  // i.e., continue with current process
}


