// test left servo

#include <Servo.h>
const int motor_left_pin = 13;
Servo motor_left;

void setup() {
  motor_left.attach(motor_left_pin);
}
void loop() {
  // confirmed 0 = full reverse
  // confirmed 90 = slow movement, adj. screw to zero
  // confirmed 180 = full forward
  motor_left.write(90);
}
