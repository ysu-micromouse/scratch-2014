// Motor Control Code
// 2014-04-01
//
// Todo (functions):
//   [X] move_forward(int Time)
//   [X] move_reverse(int Time)
//   [P] move_rotates(int Degree, bool Right)
//   [ ] move_turn(int Direction)
//   [X] sensory_wall()
//
// Todo (functionality):
//   [X] straightness correction during forward movement
//

#include <Servo.h>

//// DEBUG FLAGS
boolean one_turn = false;
boolean one_fore = false;


//// CONSTANTS
const int fSensPin = A0; // front wall sensor pin
const int rSensPin = A1; // right wall sensor pin
const int lSensPin = A2; // left wall sensor pin

const int rMotorPin = 12; // right motor pin
const int lMotorPin = 13; // left motor pin

const int mZero = 1500; // servo usec corresponding to zero speed
const int ltop = 65; // left servo adj. for top speed foreward
const int rtop = -74; // right servo adj. for top speed foreward
const int ltopR = -55; // left servo adj. for top speed reverse
const int rtopR = 74; // right servo adj. for top speed reverse


//// VARIABLES
int mv_fore_duration = 0; // duration for forward movement cmd
boolean mv_fore = false; // moving forward flag
int mv_fore_start = 0; // start time for foreward movement cmd

int mv_back_duration = 0; // duration for backward movement cmd
boolean mv_back = false; // moving backward flag
int mv_back_start = 0; // start time for backward movement cmd

int mv_right_duration = 0; // duration for right turn cmd
boolean mv_right = false; // turning right flag
int mv_right_start = 0; // start time for right turn cmd

int mv_left_duration = 0; // duration for left turn cmd
boolean mv_left = false; // turning left flag
int mv_left_start = 0; // start time for left turn cmd

int turn_adj_duration = 0; // duration for forward adjustment after turn
boolean turn_adj = false; // forward adjustment after turn flag
int turn_adj_start = 0; // start time for forward adjustment after turn

boolean stopped = true;

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

void move_backward(int Time){
  // function to set mouse in motion in the forward
  // direction for a set amount of time.
  mv_back_duration = Time;
}

void set_lMotor_speed(float rel){
  // set left motor to speed relative to top speed
  // i.e., set_lMotor_speed(0.8) sets left motor
  // speed to 80% of top speed in forward direction.
  // For positive value of rel, use ltop.
  // For negative value of rel, use ltopR (reverse).
  if (rel >= 0)
    lMotor.writeMicroseconds(mZero + ltop*rel);
  else
    lMotor.writeMicroseconds(mZero - ltopR*rel);
}

void move_stop(){
  // stops mouse movement.
  set_lMotor_speed(0);
  set_rMotor_speed(0);
  mv_fore = false;
  mv_fore_duration = 0;
  mv_back = false;
  mv_back_duration = 0;
  stopped = true;
  mv_right = false;
  mv_right_duration = 0;
  mv_left = false;
  mv_left_duration = 0;
}

void set_rMotor_speed(float rel){
  // set right motor to speed relative to top speed
  // i.e., set_rMotor_speed(-0.6) sets right motor
  // speed to -60% of top speed in reverse direction.
  // For positive value of rel, use rtop.
  // For negative value of rel, use rtopR (reverse).
  if (rel >= 0)
    rMotor.writeMicroseconds(mZero + rtop*rel);
  else
    rMotor.writeMicroseconds(mZero - rtopR*rel);
}

void read_sensors(){
  // read mouse position sensors (i.e., current
  // distance from adjacent objects)
  lDist = 10.174*exp(-0.006*analogRead(lSensPin));
  fDist = 10.174*exp(-0.006*analogRead(fSensPin));
  rDist = 10.174*exp(-0.006*analogRead(rSensPin));
  
//  Serial.print(lDist); // uncomment for debugging
//  Serial.print(" "); // uncomment for debugging
//  Serial.print(fDist); // uncomment for debugging
//  Serial.print(" "); // uncomment for debugging
//  Serial.println(rDist); // uncomment for debugging
}

boolean sensory_wall() {
  // return true if front wall is found.
  if (fDist < 5)
    return true;
  else
    return false;
}

void turn_right(int Degree) {
  mv_right_duration = 1500;
}

void turn_left(int Degree) {
  mv_left_duration = 1500;
}

void setup(){
//  Serial.begin(9600); // uncomment for debugging
  
  // set aref to 1100 mV for more precise
  // measurements from the wall sensors.
  analogReference(INTERNAL);
  
  // initialize motors
  rMotor.attach(rMotorPin);
  lMotor.attach(lMotorPin);
  set_lMotor_speed(0);
  set_rMotor_speed(0);
  
  // just testing
  delay(4000);
//  move_forward(1375); // make 4 second forward movement

}

void loop(){
  if (mv_fore_duration > 0){
    // handle foreward movement
    if (!mv_fore){
      // start movement
      mv_fore = true;
      stopped = false;
      mv_fore_start = millis();
      set_lMotor_speed(1);
      set_rMotor_speed(1);
    }
    else if (millis() - mv_fore_start >= mv_fore_duration){
      // stop movement
      set_lMotor_speed(0);
      set_rMotor_speed(0);
      mv_fore = false;
      stopped = true;
      mv_fore_duration = 0;
    }
    else {
      // continue movement
      if (!rCorr && lDist < 3){
        // Too close to left wall.  Make rightward correction.
        set_lMotor_speed(1);
        set_rMotor_speed(0.7);
        rCorr = true;
        lCorr = false;
        straight = false;
      }
      else if (!lCorr && rDist < 3){
        // Too close to right wall.  Make leftward correction.
        set_lMotor_speed(0.8);
        set_rMotor_speed(1);
        lCorr = true;
        rCorr = false;
        straight = false;
      }
      else if (!straight && rDist > 3 && lDist > 3){
        // Mouse righted.  Continue at top speed.
        set_lMotor_speed(1);
        set_rMotor_speed(1);
        straight = true;
        rCorr = false;
        lCorr = false;
      }
    }
  }
  
  else if (mv_back_duration > 0){
    // handle backward movement
    if (!mv_back){
      // start movement
      mv_back = true;
      stopped = false;
      mv_back_start = millis();
      set_lMotor_speed(-1);
      set_rMotor_speed(-1);
    }
    else if (millis() - mv_back_start >= mv_back_duration){
      // stop movement
      set_lMotor_speed(0);
      set_rMotor_speed(0);
      mv_back = false;
      stopped = true;
      mv_back_duration = 0;
    }
    else {
      // continue movement
      if (!rCorr && lDist < 4.0){
        // Too close to left wall.  Make rightward correction.
        set_lMotor_speed(-1);
        set_rMotor_speed(-0.8);
        rCorr = true;
        lCorr = false;
        straight = false;
      }
      else if (!lCorr && rDist < 4.0){
        // Too close to right wall.  Make leftward correction.
        set_lMotor_speed(-0.8);
        set_rMotor_speed(-1);
        lCorr = true;
        rCorr = false;
        straight = false;
      }
      else if (!straight && rDist > 4.0 && lDist > 4.0){
        // Mouse righted.  Continue at top speed.
        set_lMotor_speed(-1);
        set_rMotor_speed(-1);
        straight = true;
        rCorr = false;
        lCorr = false;
      }
    }
  }
  
  else if (mv_right_duration > 0){
    // handle right turn movement
    if (!mv_right){
      // start movement
      mv_right = true;
      stopped = false;
      mv_right_start = millis();
      set_lMotor_speed(1);
      set_rMotor_speed(-0.15);
    }
    else if (millis() - mv_right_start >= mv_right_duration){
      // stop movement
      set_lMotor_speed(0);
      set_rMotor_speed(0);
      mv_right_duration = 0;
      turn_adj_duration = 200;
      move_forward(1375);
    }
  }
  
  else if (mv_left_duration > 0){
    // handle left turn movement
    if (!mv_left){
      // start movement
      mv_left = true;
      stopped = false;
      mv_left_start = millis();
      set_lMotor_speed(-0.15);
      set_rMotor_speed(1);
    }
    else if (millis() - mv_left_start >= mv_left_duration){
      // stop movement
      set_lMotor_speed(0);
      set_rMotor_speed(0);
      mv_left_duration = 0;
      turn_adj_duration = 200;
      move_forward(1375);
    }
  }
  
  if (turn_adj_duration > 0){
    // Need to disable left/right turn override for a brief
    // period after a left or right turn into a new cell.
    if (!turn_adj){
      // start our forward adjustment
      turn_adj = true;
      turn_adj_start = millis();
    }
    else if (millis() - turn_adj_start >= turn_adj_duration){ // if enough time has passed after turn
      // stop our forward adjustment
      // set mv_left and mv_right flags to false
      // so we can get back to checking for possible turns
      mv_left = false;
      mv_right = false;
    }
  }
  
  read_sensors(); // update wall sensor readings
  
  if (!one_turn && mv_right && !mv_left) {
    if (rDist > 9) {
      // can make right turn
      move_stop();
      turn_right(90);
      one_turn = true;
    }
    else if (lDist > 9) {
      // go left
      move_stop();
      turn_left(90);
      one_turn = true;
    }
  }
  else if (!one_fore && stopped && fDist > 9) {
    // go straight
    move_forward(1375);
    one_fore = true;
  }
  else if (stopped && sensory_wall()) {
    // dead end
    move_stop();
    move_backward(1375);
  }
  else {
    // ??????????
  }
  
  delay(10);
}
