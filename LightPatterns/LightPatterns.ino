#include "SPI.h"
#include "Adafruit_WS2801.h"

int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels
const int numPixels = 10; // Number of LED pixels.
const uint32_t white = Color(255, 255, 255);
const uint32_t off = Color(0, 0, 0);
Adafruit_WS2801 strip = Adafruit_WS2801(numPixels, dataPin, clockPin);

// global variables
int robotState = 0; //for incoming byte
boolean DEBUG = false;
int pin1 = 10;
int pin2 = 11;
int pin3 = 12;
int statePin1 = 1;
int statePin2 = 0;
int statePin3 = 1;
int timesRun = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
}

void loop() {
  readPins(pin1, pin2, pin3);
}

int readPins(int pin1, int pin2, int pin3) {
  if(digitalRead(pin1) == 0 && digitalRead(pin2) == 0 && digitalRead(pin3) == 0) { // Forward
    patternForward();
  }
  if(digitalRead(pin1) == 0 && digitalRead(pin2) == 0 && digitalRead(pin3) == 1) { // Backward
    patternBackward();
  }
  if(digitalRead(pin1) == 0 && digitalRead(pin2) == 1 && digitalRead(pin3) == 1) { // Left
    patternLeft();
  }
  if(digitalRead(pin1) == 0 && digitalRead(pin2) == 1 && digitalRead(pin3) == 0) { // Right
    patternRight();
  }
  if(digitalRead(pin1) == 1 && digitalRead(pin2) == 1 && digitalRead(pin3) == 1) { // Picking up ball
    pickUp();
  }
  if(digitalRead(pin1) == 1 && digitalRead(pin2) == 0 && digitalRead(pin3) == 0) { // Dropping ball
    drop();
  }
  if(digitalRead(pin1) == 1 && digitalRead(pin2) == 0 && digitalRead(pin3) == 1) { // Stationary
    stationary();
  }
}

/***********************
 * Basic LED Functions *
 ***********************/
/* ~Useful Information~
 * strip.setPixelColor(int i, Color c) -- i = index of LED, c = Color object as RGB
 * It updates the designated LED pixel with a color in memory. Does not show.
 * 
 * strip.show()
 * Shows the color stored in the pixel. Use to actually update the colors physically.
 *
 * delay(int m) -- m = Number of milliseconds. (1000 milliseconds = 1 second)
 * Adds a delay to the program. Use to keep colors from changing for some time.
 *
 * The index at '0' and '(numPixels - 1)' is the back of the LEDs. Daisy chain should hang from front of robot.
 * Wiring -- Red is 5V. Blue is Ground (GND). Yellow is Data (Digital pin). Green is Clock (Digital pin).
 */

// Forward sweeps. 
void patternForward() {
 for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(index, white);
   strip.setPixelColor((numPixels - 1) - index, white);
   strip.show();
   delay(100);
 }
 
 for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(index, off);
   strip.setPixelColor((numPixels - 1) - index, off);
   strip.show();
   delay(75);
 }
 
 for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(index, white);
   strip.setPixelColor((numPixels - 1) - index, white);
   strip.show();
   delay(25);
   strip.setPixelColor(index, off);
   strip.setPixelColor((numPixels - 1) - index, off);
   strip.show();
   delay(25);
 }
}

// Backward sweeps.
void patternBackward() {
  for(int index = (numPixels / 2) - 1; index >= 0; index--) {
   strip.setPixelColor(index, white);
   strip.setPixelColor((numPixels - 1) - index, white);
   strip.show();
   delay(100);
 }
 
 for(int index = (numPixels / 2) - 1; index >= 0; index--) {
   strip.setPixelColor(index, off);
   strip.setPixelColor((numPixels - 1) - index, off);
   strip.show();
   delay(75);
 }
 
 for(int index = (numPixels / 2) - 1; index >= 0; index--) {
   strip.setPixelColor(index, white);
   strip.setPixelColor((numPixels - 1) - index, white);
   strip.show();
   delay(25);
   strip.setPixelColor(index, off);
   strip.setPixelColor((numPixels - 1) - index, off);
   strip.show();
   delay(25);
 }
}

// Counter-Clockwise sweeps.
void patternLeft() {
  for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(((numPixels / 2) - 1) - index, white);
   strip.setPixelColor((numPixels - 1) - index, white);
   strip.show();
   delay(100);
 }
 
 for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(((numPixels / 2) - 1) - index, off);
   strip.setPixelColor((numPixels - 1) - index, off);
   strip.show();
   delay(75);
 }
 
 for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(((numPixels / 2) - 1) - index, white);
   strip.setPixelColor((numPixels - 1) - index, white);
   strip.show();
   delay(25);
   strip.setPixelColor(((numPixels / 2) - 1) - index, off);
   strip.setPixelColor((numPixels - 1) - index, off);
   strip.show();
   delay(25);
 }
}

// Clockwise sweeps. 
void patternRight() {
  for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(index, white);
   strip.setPixelColor((numPixels / 2) + index, white);
   strip.show();
   delay(100);
 }
 
 for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(index, off);
   strip.setPixelColor((numPixels / 2) + index, off);
   strip.show();
   delay(75);
 }
 
 for(int index = 0; index < (numPixels / 2); index++) {
   strip.setPixelColor(index, white);
   strip.setPixelColor((numPixels / 2) + index, white);
   strip.show();
   delay(25);
   strip.setPixelColor(index, off);
   strip.setPixelColor((numPixels / 2) + index, off);
   strip.show();
   delay(25);
 }
}

void pickUp() {
  // turns on each light indiv right.
  for(int i = 0; i < 5; i++){
    strip.setPixelColor(i, Color(0, 255, 0));
    strip.show();
    delay(120);
  }
  // turns on each light indiv left.
  for(int i = 5; i < 10; i++){
    strip.setPixelColor(i, Color(0, 255, 0));
    strip.show();
    delay(120);
  }
  // turns off each light indiv right.
  for(int i = 0; i < 5; i++){
    int pixels[] = {i}; 
    fadeOut(pixels, 1, 3);  
  }
  // turns off each light indiv left.
  for(int i = 5; i < 10; i++){
    int pixels[] = {i}; 
    fadeOut(pixels, 1, 3);  
  }
  delay(120);
  // turns on each light indiv in reverse.
  for(int i = 4; i >= 0; i--){
    strip.setPixelColor(i, Color(0, 255, 0));
    strip.show();
    delay(120);
  }
  // turns off each light indiv in reverse.
  for(int i = 4; i >= 0; i--){
    int pixels[] = {i}; 
    fadeOut(pixels, 1, 3);
  }
  delay(120);
}

// @param int values for r, g, b for all pixels to be one color
void setColor(int r, int g, int b) {
  for(int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Color(r, g, b));
      strip.show();
  }
}

// sets the colors of each pixel with 2 
// different colors alternating between pixels 
void setColor(int r1, int g1, int b1, int r2, int g2, int b2) {
  for(int index = 0; index < 5; index++) {
    if(index % 2 == 0) {
      strip.setPixelColor(index, Color(r1, g1 , b1));
      strip.show();
    }
    else{
      strip.setPixelColor(index, Color(r2, g2, b2));
      strip.show();
    }
  }
}

void drop() {
  int evenPixels[3] = {0, 2, 4};
  int oddPixels[2] = {1, 3};
  // even Lights
  for(int i = 0; i < 3; i++) {
    strip.setPixelColor(evenPixels[i], Color(25, 0, 186));
  }
  strip.show();
  delay(10);
  fadeOut(evenPixels, 3, 10);
  
  // odd lights
  for(int i = 0; i < 2; i++) {
    strip.setPixelColor(oddPixels[i], Color(0, 204, 55));
  }
  strip.show();
  delay(10);
  fadeOut(oddPixels, 2, 10);
}

// @param pixels is an array of the pixel indices that should be faded
// @param length of the array
void fadeOut(int pixels[], int length, int wait) {
  if(DEBUG) { Serial.print("fade - is called\n"); }
  boolean done = false;
  int FADEVALUE = 10;
  boolean fadedPixels[length];
  for(int i = 0; i < length; i++)
    fadedPixels[i] = false;

  while(!done){
    for(int i = 0; i < length; i++) {
      int pixelIndex = pixels[i];
      // getPixelColor returns 24 bits/colors
      uint32_t c = strip.getPixelColor(pixelIndex);
      int b = c & 0x0000ff;
      c >>= 8;
      int g = c & 0x00ff;
      c >>= 8;
      int r = c;
      // checking each color indiv to see if it should
      // be subtracted by the fade value.
      if(b >= FADEVALUE)
        b -= FADEVALUE;
      else
        b = 0;
      if(g >= FADEVALUE)
        g -= FADEVALUE;
      else
        g = 0;
      if(r >= FADEVALUE)
        r -= FADEVALUE;
      else
        r = 0;
      if(b == 0 && g == 0 && r == 0){
        fadedPixels[i] = true;
      }  
      strip.setPixelColor(pixelIndex, Color(r, g , b));
    }
    strip.show();
    delay(wait);
    // set done true, then check each index and if any are false
    // set done back to false.
    done = true;
    for(int i = 0; i < length; i++)
      if(fadedPixels[i] == false)
        done = false;
  }
}

void stationary() {
  if(DEBUG) { Serial.print("stationary() - called\n"); }
  // set starting colors for the right side
  setColor(213, 131, 0, 131, 0, 213);

  int pixels[] = {0, 1, 2, 3, 4}; 
  fadeOut(pixels, 5, 50);
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
