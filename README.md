# Arduino_presence_sensing_morse_clock
An Arduino sketch to implement a RealTime clock, which senses your presence using an ultrasonic transducer, and emits the time at (arbitrary) 5 minute intervals in morse code (HH:MM).  

The RTC is available at time of posting at https://www.jaycar.com.au/arduino-compatible-real-time-clock-module/p/XC4450 
I used this library: RTCLib by NeiroN https://www.arduinolibraries.info/libraries/rtc-lib-by-neiro-n 
There's a trick with these modules. Remove the battery to reset the on-oard clock. This will forc it to take the PC datetime
on first execution.  Otherwise, comment out the if(initialised) and run it once.  

Here is the ultrasovic transducer https://www.jaycar.com.au/arduino-compatible-dual-ultrasonic-sensor-module/p/XC4442
However, I used this contributed Arduino library with success: HCSR04 by Martin Sosic Version 1.0.0 https://github.com/Martinsos/arduino-lib-hc-sr04

The buzzer is a garden variety piezo, like this: https://www.jaycar.com.au/arduino-compatible-active-buzzer-module/p/XC4424
