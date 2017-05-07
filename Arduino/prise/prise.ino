#define __AVR_ATtinyX5__
#include <RCSwitch.h>
#include <avr/sleep.h>

RCSwitch mySwitch = RCSwitch();

// pin analog moisture sensor A1
int analogInPin = A1;
// pin digital transmitter 0
int transmitterPin = 0;
int watchdog_counter = 0;
int seuil = 500;

void setup_watchdog(int ii)
{
  // 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
  // 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec

  uint8_t bb;
  if (ii > 9 ) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);

  MCUSR &= ~(1 << WDRF);
  // start timed sequence
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(analogInPin, INPUT);
  pinMode(transmitterPin, OUTPUT);
  mySwitch.enableTransmit(transmitterPin);
  //setup_watchdog(9); //Setup watchdog to go off after 8 sec
  //set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  //ADCSRA &= ~(1 << ADEN); //Disable ADC, saves ~230uA
  Serial.begin(9600);
}

//This runs each time the watch dog wakes us up from sleep
//ISR(WDT_vect) {
//  watchdog_counter++;
//}

void arroser(int sensorValue) {
  int nb = 0;
  if (sensorValue < seuil) {
    nb = 5 - (sensorValue / 100);
    for(short i=0;i< nb;i++){
      mySwitch.switchOn("10001", 1);
      delay(10000); // 1 min
      mySwitch.switchOff("10001", 1);
      delay(10000); // 1 min
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //sleep_mode(); //Go to sleep!
  //if (watchdog_counter > 30) {
  //watchdog_counter = 0;
  //ADCSRA |= (1 << ADEN); //Enable ADC
  int sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
  arroser(sensorValue);
  //ADCSRA &= ~(1 << ADEN); //Disable ADC, saves ~230uA
  //}
}
