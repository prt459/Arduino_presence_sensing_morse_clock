// This is a RealTime clock that sits silent until someone is detected by an ultrasonic sensor, 
// upon which it emits the time at 5 minute intervals in morse code.  
//
// RTC used is the DS1307 RTC connected via I2C and Wire lib
// Ultrasonic transducer/sensor used is the HCSR04
// Uses any piezo buzzer as the sounder. 
//
// Regardless of a detection from the ultrasonic sensor, this clock emits 'Westminster Chimes' (in glorious monotone) 
// on the quarter hour.  
//
// All of the settings are easily changed via the #define's at the top
//
// 13/10/2018: this is an initial version with no sensor or morse code yet!

#include <Wire.h>
#include "RTClib.h"

DS1307 rtc;

#define C 294
#define D 293
#define E 329
#define F_ 390
#define A 440
#define B 494

#define PIP_HZ 440
#define PIP_DURN_MS 5
#define CHIME_DURN_MS 1000

//time_t t;
//TimeElements te; 


int freq=PIP_HZ;
unsigned int secs=1;

void pip(int hz, int ms)
{
  tone(7, hz); 
  delay(ms);        
  noTone(7);      
}

void setup () {
  Serial.begin(9600);
  pinMode(7, OUTPUT);  // piezo 
  Wire.begin();
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}


void loop () {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
    pip(PIP_HZ, PIP_DURN_MS);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
//    Serial.print(".");
 
    DateTime now = rtc.now();
    if((now.minute() == 0) && ((now.second() == 0)))
    {
      Serial.println(" *** sound 00 chime!");
      pip(F_, CHIME_DURN_MS);
      pip(A, CHIME_DURN_MS);    
      pip(B, CHIME_DURN_MS);
      pip(F_, CHIME_DURN_MS);
    }
    else
    if((now.minute() == 15) && ((now.second() == 0)))
    {
      Serial.println(" *** sound 15 chime!");
      pip(B, CHIME_DURN_MS);
      pip(F_, CHIME_DURN_MS);
      pip(A, CHIME_DURN_MS);
      pip(C, CHIME_DURN_MS);
    }
    else
    if((now.minute() == 30) && ((now.second() == 0)))
    {
      Serial.println(" *** sound 30 chime!");
      pip(C, CHIME_DURN_MS);
      pip(A, CHIME_DURN_MS);
      pip(B, CHIME_DURN_MS);
      pip(F_, CHIME_DURN_MS);
    }
    else
    if((now.minute() == 45) && ((now.second() == 0)))
    {
      Serial.println(" *** sound 45 chime!");
      pip(F_, CHIME_DURN_MS);
      pip(B, CHIME_DURN_MS);
      pip(A, CHIME_DURN_MS);
      pip(C, CHIME_DURN_MS);
    }
   
    
    Serial.print(now.year(), DEC);     Serial.print('/');
    Serial.print(now.month(), DEC);    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);     Serial.print(':');
    Serial.print(now.minute(), DEC);   Serial.print(':');
    Serial.print(now.second(), DEC);
    
    Serial.println();
    delay(1000);
}
