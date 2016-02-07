#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// pin analog moisture sensor A2

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #13
  mySwitch.enableTransmit(13);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A2);
  mySwitch.send(sensorValue, 16);
  delay(1000);  
  //Serial.println(sensorValue);
}
