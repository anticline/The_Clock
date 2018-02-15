// clock.ino
// Get Time from DS3231 Device and distribute it to a LED Matrix with two MAX7219 as Driver
// written by Nils Becker
// 1/15/18

#include <Wire.h>
#include "DS3231.h"
#include "LedControl.h"

RTClib RTC;

LedControl lc = LedControl(10, 9, 8, 2);


void setup () {
  Serial.begin(57600);
  Wire.begin();

  lc.shutdown(0, false);
  lc.setIntensity(0, 6);
  lc.clearDisplay(0);
  lc.shutdown(1, false);
  lc.setIntensity(1, 6);
  lc.clearDisplay(1);
}

void loop () {

  delay(1000);

  DateTime now = RTC.now();

  /*
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  */

  //###############Green Ring###############

  for (int i = 0; i < 2; i++) {
    for (int z = 0; z < 6; z++) {
      lc.setLed(i, z, 6, true);
    }
  }

  //###############Set Hour###############

  if (now.hour() < 6 ) {
    lc.setLed(now.hour() / 6, now.hour(), 7, true);
    lc.setLed(now.hour() / 6, now.hour() - 1, 7, false);
  }

  else if (now.hour() >= 6 && now.hour() < 12){
    lc.setLed(now.hour() / 6, now.hour() - 6, 7, true);
    lc.setLed(now.hour() / 6, now.hour() - 7, 7, false);
  }

  else if (now.hour() >= 12 && now.hour() < 18){
    lc.setLed((now.hour()-12) / 6, now.hour() -12, 7, true);
    lc.setLed((now.hour()-12) / 6, now.hour() - 13, 7, false);
    }

  else {
    lc.setLed((now.hour()-12) / 6, now.hour() - 18, 7, true);
    lc.setLed((now.hour()-12) / 6, now.hour() - 19, 7, false);
    }
  

  //###############Reset Hours when Controller cahnges###############

  if (now.hour() == 6 || now.hour() == 18)
    lc.setLed(0, 5, 7, false);

  else if (now.hour() == 0 || now.hour() == 12)
    lc.setLed(1, 5, 7, false);



//###############Set Minutes###############

  //###############Get Controller###############

  int c = 0;
  int m = 0;
  int x = 0;
  
  if (now.minute() < 30)
    c = 0;

  else
    c = 1;

  //###############Get Row###############

  int r = 0;

  if (now.minute() < 30)
    r = now.minute() / 5;

  else
    r = (now.minute() - 30) / 5;

  //###############Get Seg and set###############

  if (now.minute() % 10 < 5) {
    for (m = 1; m < (now.minute() % 10) + 2; m++) {
      lc.setLed(c, r, m, true);
    }
  }

  else {
    for (m = 1; m < (now.minute() % 10) - 3; m++) {
      lc.setLed(c, r, m, true);
    }
  }

  //###############Reset row before###############

  if (now.minute() % 5 == 0 && now.minute() != 30 && now.minute() != 0) {
    for (x = 1; x < 6; x++) {
      lc.setLed(c, r - 1, x, false);
    }
  }

  if (now.minute() == 30) {
    for (x = 1; x < 6; x++) {
      lc.setLed(c - 1, r + 5, x, false);
    }
  }

  if (now.minute() == 0) {
    for (x = 1; x < 6; x++) {
      lc.setLed(c + 1, r + 5, x, false);
    }
  }


  Serial.println(c);
  Serial.println(r);
  Serial.println(m);

}

