#include "SPI.h"
#include "Adafruit_WS2801.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(5, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Examples:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin, WS2801_GRB);
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

void setup() {
  Serial.begin(9600);
    
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
}

void loop() {
  // Some example procedures showing how to display to the pixels
  
//  colorWipe(Color(255, 0, 0), 0);
//  colorWipe(Color(0, 255, 0), 50);
//  colorWipe(Color(0, 0, 255), 100);
    stationary();
}

void test(uint16_t index){
  uint32_t c = strip.getPixelColor(index) ;
  int b = c & 0x0000ff;
  c >>= 8;
  int g = c & 0x00ff;
  c >>= 8;
  int r = c;
  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\n");
  
  
}

void fadeOut() {
  Serial.print("fade - is called\n");
  boolean done = false;
  int FADEVALUE = 10;
  boolean fadedPixels[strip.numPixels()];
  for(int i = 0; i < strip.numPixels(); i++)
    fadedPixels[i] = false;

  while(!done){
    for(int i = 0; i < strip.numPixels(); i++) {
      // getPixelColor returns 24 bits/colors
      uint32_t c = strip.getPixelColor(i);
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
      strip.setPixelColor(i, Color(r, g , b));
    }
    strip.show();
    delay(40);
    // set done true, then check each index and if any are false
    // set done back to false.
    done = true;
    for(int i = 0; i < strip.numPixels(); i++)
      if(fadedPixels[i] == false)
        done = false;
  }
}

void stationary() {
  Serial.print("stationary() - called\n");
  // set starting colors for the right side
  for(int index = 0; index < 5; index++) {
    if(index % 2 == 0) {
      strip.setPixelColor(index, Color(213, 131 , 0));
      strip.show();
    }
    else{
      strip.setPixelColor(index, Color(24, 0, 213));
      strip.show();
    }
  }
  fadeOut();
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
