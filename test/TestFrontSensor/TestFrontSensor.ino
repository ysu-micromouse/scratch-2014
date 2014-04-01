/*
  Analog input, serial output
  
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int front_raw = 0;
float sensorValue = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  analogReference(2); // 2 = INTERNAL1V1 (i.e., 1.1V aref)
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  front_raw = analogRead(analogInPin);
  sensorValue = 10.174*exp(-0.006*front_raw);
  // map it to the range of the analog out:

  // print the results to the serial monitor:
  Serial.print(front_raw);  
  Serial.print(" ");
  Serial.print(sensorValue);
  Serial.println(" cm");  

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
