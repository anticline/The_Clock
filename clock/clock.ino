// clock.ino
// Get Time from DS3231 Device and distribute it to a LED Matrix with two MAX7219 as Driver
// written by Nils Becker
// 1/15/18

#define DEBUG 0

#include <Wire.h>
#include <DS3232RTC.h>
#include <LedControl.h>
#include <TimeLib.h>

LedControl lc = LedControl(10, 9, 8, 2);


void setup () {

  lc.shutdown(0, false);
  lc.setIntensity(0, 6);
  lc.clearDisplay(0);
  lc.shutdown(1, false);
  lc.setIntensity(1, 6);
  lc.clearDisplay(1);

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  //setSyncInterval();          // function to set interval of setSync in sec (default:5min)

  if (DEBUG){
    Serial.begin(9600);
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      
    
    }
}

void loop () {

  if (DEBUG){
  
    Serial.print(year(), DEC);
    Serial.print('/');
    Serial.print(month(), DEC);
    Serial.print('/');
    Serial.print(day(), DEC);
    Serial.print(' ');
    Serial.print(hour(), DEC);
    Serial.print(':');
    Serial.print(minute(), DEC);
    Serial.print(':');
    Serial.print(second(), DEC);
    Serial.println();
  
  }

  if (timeStatus() == timeSet) {
    displayTime();
    }

  else {
    blinkInnerRing();
    }

  delay(1000);
}

void blinkInnerRing() {

  for (int i = 0; i < 2; i++) {
    for (int z = 0; z < 6; z++) {
      lc.setLed(i, z, 1, true);
    }
  }
  delay(500);

  lc.clearDisplay(0);
  lc.clearDisplay(1);
  delay(500);

}

void displayTime(){
  
  //###############Green Ring###############

  for (int i = 0; i < 2; i++) {
    for (int z = 0; z < 6; z++) {
      lc.setLed(i, z, 6, true);
    }
  }

  //###############Set Hour###############

  if (hour() < 6 ) {
    lc.setLed(hour() / 6, hour(), 7, true);
    lc.setLed(hour() / 6, hour() - 1, 7, false);
  }

  else if (hour() >= 6 && hour() < 12){
    lc.setLed(hour() / 6, hour() - 6, 7, true);
    lc.setLed(hour() / 6, hour() - 7, 7, false);
  }

  else if (hour() >= 12 && hour() < 18){
    lc.setLed((hour()-12) / 6, hour() -12, 7, true);
    lc.setLed((hour()-12) / 6, hour() - 13, 7, false);
    }

  else {
    lc.setLed((hour()-12) / 6, hour() - 18, 7, true);
    lc.setLed((hour()-12) / 6, hour() - 19, 7, false);
    }
  

  //###############Reset Hours when Controller cahnges###############

  if (hour() == 6 || hour() == 18)
    lc.setLed(0, 5, 7, false);

  else if (hour() == 0 || hour() == 12)
    lc.setLed(1, 5, 7, false);



//###############Set Minutes###############

  //###############Get Controller###############

  int c = 0;
  int m = 0;
  int x = 0;
  
  if (minute() < 30)
    c = 0;

  else
    c = 1;

  //###############Get Row###############

  int r = 0;

  if (minute() < 30)
    r = minute() / 5;

  else
    r = (minute() - 30) / 5;

  //###############Get Seg and set###############

  if (minute() % 10 < 5) {
    for (m = 1; m < (minute() % 10) + 2; m++) {
      lc.setLed(c, r, m, true);
    }
  }

  else {
    for (m = 1; m < (minute() % 10) - 3; m++) {
      lc.setLed(c, r, m, true);
    }
  }

  //###############Reset row before###############

  if (minute() % 5 == 0 && minute() != 30 && minute() != 0) {
    for (x = 1; x < 6; x++) {
      lc.setLed(c, r - 1, x, false);
    }
  }

  if (minute() == 30) {
    for (x = 1; x < 6; x++) {
      lc.setLed(c - 1, r + 5, x, false);
    }
  }

  if (minute() == 0) {
    for (x = 1; x < 6; x++) {
      lc.setLed(c + 1, r + 5, x, false);
    }
  }

  if (DEBUG){
  
    Serial.println(c);
    Serial.println(r);
    Serial.println(m);

  }
  
}

