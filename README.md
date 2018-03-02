# The_Clock
Arduino Code for a pseudo analog LED Clock

## Status

###########--Work in progress--##########

Simple Arduino Code to read the Time from a DS3231 RTC Device and
distribute it to a selfmade LED-Matrix.

ToDo:

- add drawings for the matrix and the wiring

- replace arduino nano with an esp, because of wifi and the ability to configure it remotely
 and the ability to sync time from a timeserver

## Libraries

- Wire
- DS3232RTC (https://github.com/JChristensen/DS3232RTC)
- TimeLib (https://github.com/PaulStoffregen/Time)
- LedControl (https://github.com/wayoda/LedControl)
