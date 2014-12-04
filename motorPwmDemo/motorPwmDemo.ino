/*
 Fading

 This example shows how to fade an LED using the analogWrite() function.

 The circuit:
 * using L298N H-bridge board
 * hbridge 
 * pin 9 PWM - to H-bridge In1 (motor A, forward)
 * pin 10 PWM - to H-bridge In2 (motor A, reverse)
 */
//
int forwardPin = 9;
int reversePin = 10;
int maxValue = 255; /* 1-255 */
int fadeSpeed = 25; /* 1-255, lower is slower, 5 typical */
int pauseTime = 500; /* msec to pause between forward and reverse */
int runTime = 1000; /* msec to run full speed before slowing */
//
void setup() {
  analogWrite(reversePin, 0);
  analogWrite(forwardPin, 0);
}

void loop() {
  //
  // forward - ramp from off to full
  //
  for (int fadeValue = 0 ; fadeValue <= maxValue; fadeValue += fadeSpeed) {
    analogWrite(forwardPin, fadeValue);
    delay(30);
  }
  analogWrite(forwardPin, maxValue);
  delay(runTime);
  //
  // forward - ramp from full to off
  //
  for (int fadeValue = maxValue ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    analogWrite(forwardPin, fadeValue);
    delay(30);
  }
  analogWrite(forwardPin, 0);
  delay(pauseTime);
  //
  // reverse - ramp from off to full
  //
  for (int fadeValue = 0 ; fadeValue <= maxValue; fadeValue += fadeSpeed) {
    analogWrite(reversePin, fadeValue);
    delay(30);
  }
  analogWrite(reversePin, maxValue);
  delay(runTime);
  //
  // reverse - ramp from full to off
  //
  for (int fadeValue = maxValue ; fadeValue >= 0; fadeValue -= fadeSpeed) {
    analogWrite(reversePin, fadeValue);
    delay(30);
  }
  analogWrite(reversePin, 0);
  delay(pauseTime);
}


