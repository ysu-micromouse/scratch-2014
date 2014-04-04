/*
  Analog input, serial output
  
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int fSensPin = A3;  // Analog input pin that the potentiometer is attached to
const int rSensPin = A2;
const int lSensPin = A1;
const int bSensPin = A0;

float fDist = 0; // front distance (cm)
float rDist = 0; // left distance (cm)
float lDist = 0; // right distance (cm)
float bDist = 0; // back distance (cm)

void setup() {
  // initialize serial communications at 9600 bps:
  analogReference(2); // 2 = INTERNAL1V1 (i.e., 1.1V aref)
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  lDist = 10.174*exp(-0.006*analogRead(lSensPin));
  fDist = 10.174*exp(-0.006*analogRead(fSensPin));
  rDist = 10.174*exp(-0.006*analogRead(rSensPin));
  bDist = 10.174*exp(-0.006*analogRead(bSensPin));
  // map it to the range of the analog out:

  // print the results to the serial monitor:
  Serial.print(lDist);  
  Serial.print(" ");
  Serial.print(fDist);  
  Serial.print(" ");
  Serial.print(rDist);
  Serial.print(" ");
  Serial.print(bDist);
  Serial.println(" cm");  

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}
