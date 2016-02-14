#define __AVR_ATtinyX5__
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// pin analog moisture sensor A1
int analogInPin = A1;
// pin digital transmitter 0
int transmitterPin = 0;
// pin digital output
int digitalOutPin = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(analogInPin, INPUT);
  //pinMode(transmitterPin, OUTPUT);
  //pinMode(digitalOutPin, OUTPUT);
  mySwitch.enableTransmit(transmitterPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(analogInPin);
  mySwitch.send(sensorValue, 16);
  delay(1000);  
}
