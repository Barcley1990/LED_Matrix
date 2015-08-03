/* 
* Snake.cpp
*
* Created: 01.08.2015 19:57:01
* Author: Tobias Nuss
*/

#include "Pixels.h"
#include "math.h"

#define BRIGHTNESS 64


Pixels::Pixels(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
  m_height = h;
  m_width = w;
  char m_quitButton = qb;
}
char QuitButton;

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Pixels::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return MyLedMatrix::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return MyLedMatrix::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return MyLedMatrix::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

int Pixels::Rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< MyLedMatrix::numPixels(); i++) {
      if( (char)Serial1.read() == 'O') {        
        return 0;
        break;    
      }
      MyLedMatrix::setPixelColor(i, Wheel(((i * 256 / MyLedMatrix::numPixels()) + j) & 255));
    }
    MyLedMatrix::show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
int Pixels::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<MyLedMatrix::numPixels(); i++) {
    if( (char)Serial1.read() == 'O') {        
        return 0;
        break;    
      }
      MyLedMatrix::setPixelColor(i, c);
      MyLedMatrix::show();
      delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
int Pixels::rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< MyLedMatrix::numPixels(); i++) {
      if( (char)Serial1.read() == 'O') {        
        return 0;
        break;    
      }
      MyLedMatrix::setPixelColor(i, Wheel(((i * 256 / MyLedMatrix::numPixels()) + j) & 255));
    }
    MyLedMatrix::show();
    delay(wait);
  }
}

//Theatre-style crawling lights with rainbow effect
int Pixels::theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < MyLedMatrix::numPixels(); i=i+3) {
          if( (char)Serial1.read() == 'O') {        
          return 0;
          break;    
      }
          MyLedMatrix::setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        MyLedMatrix::show();
       
        delay(wait);
       
        for (int i=0; i < MyLedMatrix::numPixels(); i=i+3) {
          MyLedMatrix::setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

















