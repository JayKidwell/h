/*
 The circuit:
 * using L298N H-bridge board
 * hbridge 
 * pin 9 PWM - to H-bridge In1 (motor A, forward)
 * pin 10 PWM - to H-bridge In2 (motor A, reverse)
 */
//
int rightForwardPin = 5;
int rightReversePin = 6;
int leftForwardPin = 9;
int leftReversePin = 10;
int maxValue = 255; /* 1-255 */
int fadeSpeed = 25; /* 1-255, lower is slower, 5 typical */
int pauseTime = 500; /* msec to pause between forward and reverse */
int runTime = 2000; /* msec to run full speed before slowing */
// ==========================================================================================
// setup
//
void setup() {
  moveStop();
}
// ==========================================================================================
// loop
// 
// each attached device has a currentLevel, a targetLevel, and an acceleration.
// changes are made by modifying the targetLevel, and optionally the acceperation
// the loop translates those changes into motion changes
//
void loop() {
  //
  // forward - ramp from off to full
  //
  for (int fadeValue = 0 ; fadeValue <= maxValue; fadeValue += fadeSpeed) {
    analogWrite(leftForwardPin, fadeValue);
    analogWrite(rightForwardPin, fadeValue);
    delay(30);
  }
  analogWrite(leftForwardPin, maxValue);
  analogWrite(rightForwardPin, maxValue);
  delay(runTime);
  //
  // forward - ramp from full to off
  //
  for (int fadeValue = maxValue ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    analogWrite(leftForwardPin, fadeValue);
    analogWrite(rightForwardPin, fadeValue);
    delay(30);
  }
  moveStop();
  delay(pauseTime);
  //
  // reverse - ramp from off to full
  //
  for (int fadeValue = 0 ; fadeValue <= maxValue; fadeValue += fadeSpeed) {
    analogWrite(leftReversePin, fadeValue);
    analogWrite(rightReversePin, fadeValue);
    delay(30);
  }
  analogWrite(leftReversePin, maxValue);
  delay(runTime);
  //
  // reverse - ramp from full to off
  //
  for (int fadeValue = maxValue ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    analogWrite(leftReversePin, fadeValue);
    analogWrite(rightReversePin, fadeValue);
    delay(30);
  }
  moveStop();
  delay(pauseTime);
}
/* ======================================================================
 * Stop 
*/
void moveStop (){
  analogWrite(leftForwardPin, 0);
  analogWrite(leftReversePin, 0);
  analogWrite(rightForwardPin, 0);
  analogWrite(rightReversePin, 0);
}
/* ======================================================================
 * Forward 
*/
void moveForward() {
  
}

