#include <Wire.h>
#include <Adafruit_AS7341.h>
#include "FastLED.h"

Adafruit_AS7341 as7341;
CRGB leds[8];

#define pir1 2
#define pir2 3
#define pir3 4
#define pir4 5
#define lights 12

int whichOn = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    delay(1);
  }

  if (!as7341.begin()){
 //   Serial.println("Could not find AS7341");
    while (1) { delay(10); }
  }

  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);

  FastLED.addLeds<NEOPIXEL, lights>(leds, 8);

  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);
}

void loop() {
  // color sensor
  uint16_t readings[12];

  if (!as7341.readAllChannels(readings)){
  //  Serial.println("Error reading all channels!");
    return;
  }

  if(readings[9] >= 65000 && readings[10] < 32000){
 //   Serial.println("Detecting Red");
  }

  if((readings[7] >= 65000 || readings[6] >= 65000) && readings[10] < 32000){
  //  Serial.println("Detecting Green");
  }

  if(readings[2] >= 65000 && readings[10] < 32000 ){
 //   Serial.println("Detecting Blue");
  }

  bool pir1_value = digitalRead(pir1);
  bool pir2_value = digitalRead(pir2);
  bool pir3_value = digitalRead(pir3);
  bool pir4_value = digitalRead(pir4);

  if(pir1_value == 1){
    whichOn = 1;
  //  Serial.println(whichOn);
  }
  else if(pir2_value == 1){
    whichOn = 2;
   // Serial.println(whichOn);
  }
  else if(pir3_value == 1){
    whichOn = 3;
  //  Serial.println(whichOn);
  }
  else if(pir4_value == 1){
    whichOn = 4;
   // Serial.println(whichOn);
  }else{
    whichOn = 0;
  }
 
  // Send the value of whichOn over the serial port
  Serial.print("whichOn=");
  Serial.println(whichOn);

  FastLED.showColor(CHSV(255, 255, 100));
  FastLED.show();

  delay(100);
}
