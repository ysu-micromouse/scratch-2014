// test right servo

#include <Servo.h>
const int motor_right_pin = 12;
Servo motor_right;

void setup() {
  motor_right.attach(motor_right_pin);
}
void loop() {
  // confirmed 0 = full forward
  // confirmed 90 = slow movement, adj. screw to zero
  // confirmed 180 = full reverse
  motor_right.write(90);
}
