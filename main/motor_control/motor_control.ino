// Motor Control Code
// 2014-04-01
//
// Todo (functions):
//   [X] move_forward(int Time)
//   [ ] move_reverse(int Time)
//   [ ] move_rotates(int Degree, bool Right)
//   [ ] move_turn(int Direction)
//   [ ] sensory_wall()
//
// Todo (functionality):
//   [P] straightness correction during forward movement
//

#include <Servo.h>


//// CONSTANTS
const int fSensPin = A0; // front wall sensor pin
const int rSensPin = A1; // right wall sensor pin
const int lSensPin = A2; // left wall sensor pin

const int rMotorPin = 12; // right motor pin
const int lMotorPin = 13; // left motor pin

const int mZero = 1500; // servo usec corresponding to zero speed
const int ltop = 94; // left servo adj. for top speed foreward
const int rtop = -200; // right servo adj. for top speed foreward


//// VARIABLES
int mv_fore_duration = 0; // duration for forward movement cmd
boolean mv_fore = false; // moving forward flag
int mv_fore_start = 0; // start time for foreward movement cmd

// state of current mouse regarding forward travel
boolean straight = true; // mouse traveling straight down center
boolean rCorr = false; // mouse making rightward correction
boolean lCorr = false; // mouse making leftward correction

// distance measurements in [cm]
// reading > 10 if no object detected
float lDist; // current leftward distance measurement
float rDist; // current rightward distance measurment
float fDist; // current forward distance measurment

Servo rMotor; // right servo object
Servo lMotor; // left servo object


void move_forward(int Time){
  // function to set mouse in motion in the forward
  // direction for a set amount of time.
  mv_fore_duration = Time;
}

void set_lMotor_speed(float rel){
  // set left motor to speed relative to top speed
  // i.e., set_lMotor_speed(0.8) sets left motor
  // speed to 80% of top speed in forward direction.
  lMotor.writeMicroseconds(mZero + ltop*rel);
}

void set_rMotor_speed(float rel){
  // set right motor to speed relative to top speed
  // i.e., set_rMotor_speed(-0.6) sets right motor
  // speed to -60% of top speed in reverse direction.
  rMotor.writeMicroseconds(mZero + rtop*rel);
}

void read_sensors(){
  // read mouse position sensors (i.e., current
  // distance from adjacent objects)
  lDist = 10.174*exp(-0.006*analogRead(lSensPin));
  fDist = 10.174*exp(-0.006*analogRead(fSensPin));
  rDist = 10.174*exp(-0.006*analogRead(rSensPin));
}

void setup(){
  // set aref to 1100 mV for more precise
  // measurements from the wall sensors.
  analogReference(INTERNAL);
  
  // initialize motors
  rMotor.attach(rMotorPin);
  lMotor.attach(lMotorPin);
  set_lMotor_speed(0);
  set_rMotor_speed(0);
  
  // just testing
  move_forward(5000); // make 5 second forward movement
}

void loop(){
  if (mv_fore_duration > 0){
    // handle foreward movement
    if (!mv_fore){
      // start movement
      mv_fore = true;
      mv_fore_start = millis();
      set_lMotor_speed(1);
      set_rMotor_speed(1);
    }
    else if (millis() - mv_fore_start >= mv_fore_duration){
      // stop movement
      set_lMotor_speed(0);
      set_rMotor_speed(0);
      mv_fore = false;
      mv_fore_duration = 0;
    }
    else {
      // continue movement
      if (!rCorr && lDist < 3.5){
        // Too close to left wall.  Make rightward correction.
        set_lMotor_speed(0.6);
        set_rMotor_speed(1);
        rCorr = true;
        lCorr = false;
        straight = false;
      }
      else if (!lCorr && rDist < 3.5){
        // Too close to right wall.  Make leftward correction.
        set_lMotor_speed(1);
        set_rMotor_speed(0.6);
        lCorr = true;
        rCorr = false;
        straight = false;
      }
      else if (!straight && rDist > 3.5 && lDist > 3.5){
        // Mouse righted.  Continue at top speed.
        set_lMotor_speed(1);
        set_rMotor_speed(1);
        straight = true;
        rCorr = false;
        lCorr = false;
      }
    }
  }
  
  read_sensors(); // update wall sensor readings
  delay(10);
}
