//@author Mohammed-Yasir Suara
//SN: 101088810

#include <FastLED.h>
#include <Wire.h>
#include "RTClib.h"

#define NUM_LEDS 30 //number of LEDs  
#define DATA_PIN 6 //data line, ground and power
#define BRIGHTNESS 255 // LED brightness
CRGB LEDs[NUM_LEDS]; //the array of LEDs

// Set LEDs colour
CRGB colour = CRGB::White;   
RTC_DS3231 rtc;

int brightButton = 10;
int alarmPin = 11;
int alarmButton = 12;
const int frequency = 600;
const int period = 500;

int count = BRIGHTNESS;
int fade = BRIGHTNESS/2;

 int h1;
 int h2; 
 int m1;
 int m2;
 
String alarmT;
int i;

void setup () {
  // Initialize LED strip
  FastLED.delay(3000);
  // Check if you're LED strip is a RGB or GRB version (third parameter)
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LEDs, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS); //set brightness for all LEDs

  Serial.begin(9600);
  while (!Serial) { /* Wait until serial is ready */ }
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, set the time!");
    // line below sets the RTC to the date & time this code is compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line below sets the RTC to the time and time the compiler chooses, for example to set
    // December 07, 2019 at 8am you would type:
    // rtc.adjust(DateTime(2019, 12, 07, 8, 0, 0));
  }
  pinMode(alarmPin, OUTPUT);
  
  pinMode(alarmButton, INPUT);

  pinMode(brightButton, INPUT);
}

void loop () {
  DateTime now = rtc.now();

  //24 hour clock format
  h1 = now.hour() / 10;
  h2 = now.hour() % 10;
  m1 = now.minute() / 10;
  m2 = now.minute() % 10;

  displayTime(0, m2);    
  displayTime(7, m1);
  displayTime(16, h2);    
  displayTime(23, h1);    

  FastLED.show();

  brightness();

  checkInput();

  muteAlarm();
  
  delay(2000);
}

void checkInput(){
  if (Serial.available()){
    alarmT = Serial.readStringUntil('\n');
    i = alarmT.toInt();
    checkAlarm(i);
  }
}

/*@author Leon van den Beukel (displayTime)
 https://github.com/leonvandenbeukel/3D-7-Segment-Digital-Clock (displayTime)
*/

void displayTime(int index, int number) {

  byte numbers[] = {
    0b00111111, // 0    
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9   
  };

  for (int i = 0; i < 7; i++) {
    LEDs[i + index] = ((numbers[number] & 1 << i) == 1 << i) ? colour : CRGB::Black;
  }
  // Dots between the hours and minutes
  LEDs[14] = colour;
  LEDs[15] = colour;
}

void brightness(){
   if(digitalRead(brightButton) == HIGH){
      FastLED.setBrightness(BRIGHTNESS-fade);//reduces lights brightness by 50%
      digitalRead(brightButton)=LOW;
   }
   else{
    digitalRead(brightButton)=LOW;
   }
}

void checkAlarm(int j){
  int j1= j/100;
  int j2= j%100; 
  if((j1==((h1*10)+h2)) && (j2 == ((m1*10)+m2))){//alarm time == rtc time
    tone(alarmPin,frequency,period);
    delay(1000);
    FastLED.show();
    delay(500);
  }
}

void muteAlarm(){
  if(digitalRead(alarmButton)==HIGH){
      noTone(alarmPin); //mutes the alarm
      digitalRead(alarmButton)==HIGH;
  }
  else{
    digitalRead(alarmButton==LOW);
    FastLED.show()
  }
}

void changeLED(){
  //get LED colour from Pi;
  if(recolour==RED){
    for(i=0; i<30; i++){
     LEDs[i]=CRGB::Red;
  }
  else if(recolour==GREEN){
    for(i=0; i<30; i++){
     LEDs[i]=CRGB::Green;
  }
   else{
     LEDs[i]=CRGB::Blue;
  }
  
}

