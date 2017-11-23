#include <FastLED.h>


/********BASIC SETTINGS********/

// the data pin for the NeoPixels
#define DATA_PIN 6

// How many LEDs we will be using, charge according to your needs
#define NUM_LEDS 60

//time for a full loop in milliseconds. e.g : 5000ms is 5s.
#define TIME_LOOP 2500

//size of the line
//e.g : NUM_LEDS to have a wave of the size of your LED strip that you already defined
//20 (or anything else) to have a shorter wave than the length of your LED strip
#define LINE_LENGTH 20

/*
   Define the color of the wave. You can use RGB, HEX or HSV color.
   Color values must be between 0 & 255.
   e.g for red color:
   RGB : const CRGB defaultColor = CRGB(255,0,0);
   HEX : const CRGB defaultColor = CRGB(0xFF0000);
   HSV : const CRGB defaultColor = CHSV(0,255,255);
*/
const CRGB defaultColor = CRGB(0, 255, 0);


/******************CODE*****************/
/**************DO NOT TOUCH*************/
/*********unless you really need********/

//time variable
unsigned long time;

unsigned int halfTime = TIME_LOOP / 2;

CRGB leds[NUM_LEDS];

int movementSize = NUM_LEDS - LINE_LENGTH;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  //strip.setBrightness(60);
  Serial.begin(9600);
}

void loop() {
  renderLEDs();
}

void renderLEDs() {
  time = millis();
  //difference in time
  float startPos;
  if ( (time % TIME_LOOP ) < halfTime) {
    startPos = ((float)(time % halfTime) / halfTime) * movementSize;
  }
  else {
    startPos = movementSize - ((float)(time % halfTime) / halfTime) * movementSize;
  }

  int roundedPos = round(startPos);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i > roundedPos && i< roundedPos+ LINE_LENGTH) {
      leds[i] = defaultColor;
    }
    else {
      leds[i] = CRGB(0 , 0 , 0);
    }
  }

  FastLED.show();

}

