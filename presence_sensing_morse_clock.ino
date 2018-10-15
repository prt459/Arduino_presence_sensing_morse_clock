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

#define C 294
#define D 293
#define E 329
#define F_ 390
#define A 440
#define B 494

#define PIP_HZ 440
#define PIP_DURN_MS 5
#define CW_TONE_HZ 700
#define CHIME_DURN_MS 1000
#define CW_DASH_LEN        5  // length of dash (in dots)
#define PIN_TONE_OUT 7        // piez0/buzzer/transducer on this Arduino digital pin

int dot_length_ms = 60;    // keyer base speed (60 equates to 10 w.p.m.)
int freq=PIP_HZ;           // freq of the second pip
// unsigned int secs=1;
byte j,k;  
DS1307 rtc;                // the RTC object


void send_dot() {
  delay(dot_length_ms);  // wait for one dot period (space)
  tone(PIN_TONE_OUT, CW_TONE_HZ);
  Serial.print(".");
  delay(dot_length_ms);  // key down for one dot period
  noTone(PIN_TONE_OUT);
}

void send_dash() {
  delay(dot_length_ms);  // wait for one dot period (space)
  tone(PIN_TONE_OUT, CW_TONE_HZ);
  Serial.print("-");
  delay(dot_length_ms * CW_DASH_LEN);  // key down for CW_DASH_LEN dot periods
  noTone(PIN_TONE_OUT);
}

void send_letter_space() {
  delay(dot_length_ms * 4);  // wait for 3 dot periods
  Serial.print(" ");
}

void send_digit(byte n) {
  // n is the clock digit to be enunciated  
  Serial.print("send_digit(");
  Serial.print(n);
  Serial.println(")");
  if((n>=1)&&(n<=4))  // n == 1, 2, 3, 4 or 5
  {   
    for(j=1; j<=n); j++) send_dot(); 
    for(k=5; k>n; k--) send_dash(); 
  }
  else
  {
    // n == 6, 7, 8, 9, 0
    for(j=6; j<=n); j++) send_dash(); 
    for(k=10; k>n; k--) send_dot(); 
  };
  send_letter_space();
}

void pip(int hz, int ms)
{
  tone(PIN_TONE_OUT, hz); 
  delay(ms);        
  noTone(PIN_TONE_OUT);      
}

void setup () {
  Serial.begin(9600);
  pinMode(PIN_TONE_OUT, OUTPUT);  // piezo 
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

    // get the time HHMM as four bytes and send each of the 4 digits in morse
    byte h = (byte)(now.hour()/10);  // hour MSB
    if(h>0) send_digit(h);
    h = now.hour()%10;               // hour LSB
    send_digit(h);

    // send ':'
    // send_dash(); send_dash(); send_dash(); send_dot(); send_dot(); send_dot();

    // alternate option; send a two-tone pip-pip
    pip(CW_TONE_HZ, dot_length_ms);  
    pip(CW_TONE_HZ-100, dot_length_ms);  
    send_letter_space()

    h = (byte)now.minute()/10;  // minute MSB
    send_digit(h);
    h = now.minute()%10;        // minute LSB
    send_digit(h);
  
    delay(10000);
}
