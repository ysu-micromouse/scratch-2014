#include <Servo.h>
const int motor_right_pin = 12;
Servo motor_right;
const int motor_left_pin = 13;
Servo motor_left;
const int fSensPin = A0;  // Analog input pin that the potentiometer is attached to
const int rSensPin = A1;
const int lSensPin = A2;
const int ltop = 94;
const int rtop = -200;
const int mstop = 1500;
boolean lefting = false;
boolean righting = false;
boolean straighting = true;

float fDist = 0; // front distance (cm)
float rDist = 0; // left distance (cm)
float lDist = 0; // right distance (cm)

void setup() {
  analogReference(2); // 2 = INTERNAL1V1 (i.e., 1.1V aref)
  motor_right.attach(motor_right_pin);
  motor_left.attach(motor_left_pin);
  motor_right.writeMicroseconds(1500);
  motor_left.writeMicroseconds(1500);
  delay(5000);
  
  // start stright at top speed
  motor_right.writeMicroseconds(mstop + rtop);
  motor_left.writeMicroseconds(mstop + ltop);
}

void loop() {  
  // read the analog in value:
  lDist = 10.174*exp(-0.006*analogRead(lSensPin));
  fDist = 10.174*exp(-0.006*analogRead(fSensPin));
  rDist = 10.174*exp(-0.006*analogRead(rSensPin));
  
  // sensors should read about 4.87 cm when centered
  if (!righting && lDist < 3.5){
  // too close to left wall, shift right
  // assuming we're going at top speed, then
  // we must slow down the right wheel to shift
  // right
    motor_left.writeMicroseconds(mstop + ltop);
    motor_right.writeMicroseconds(mstop + rtop*0.8);
    righting = true;
    lefting = false;
    straighting = false;
  }
  else if (!lefting && rDist < 3.5){
  // too close to right wall, shift left
  // assuming we're going at top speed, then
  // we must slow down the left wheel to shift
  // left
    motor_right.writeMicroseconds(mstop + rtop);
    motor_left.writeMicroseconds(mstop + ltop*0.8);
    righting = false;
    lefting = true;
    straighting = false;
  }
  else if (!straighting && rDist > 3.5 && lDist > 3.5){
  // centered, keep going.
  motor_left.writeMicroseconds(mstop + ltop);
  motor_right.writeMicroseconds(mstop + rtop);
  righting = false;
  lefting = false;
  straighting = true;
  }
  
  delay(10);
}
