/* 
* Snake.cpp
*
* Created: 01.08.2015 19:57:01
* Author: Tobias Nuss
*/

#include "Pixels.h"
#include "MyLedMatrix.h"
#include "math.h"

//  uint32_t color;
//  uint8_t red, blue, green;
//  red   = (color >> 16);
//  blue  = (color >> 8);
//  green = (color >> 0);


#define BRIGHTNESS 64


Pixels::Pixels(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
  m_height = h;
  m_width = w;
  m_numleds = l;
  char m_quitButton = qb;
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Pixels::Wheel(byte WheelPos) 
{
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

uint8_t cnt = 0;
int Pixels::Rainbow(uint8_t wait, uint8_t rerun) 
{
  if(cnt == rerun) {
    cnt = 0;
    return 0;
    //break;
  }
    uint16_t i, j;
    for(j=0; j<256; j++) { // 1 cycle of all colors on wheel
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
    cnt++;
}

// Fill the dots one after the other with a color
int Pixels::colorWipe(uint32_t c, uint8_t wait, uint8_t rerun) 
{
  if(cnt == rerun) {
    cnt = 0;
    return 0;
    //break;
  }
  for(uint16_t i=0; i<MyLedMatrix::numPixels(); i++) {   
    if( (char)Serial1.read() == 'O') {        
        return 0;
        break;    
      }
      MyLedMatrix::setPixelColor(i, c);
      MyLedMatrix::show();
      delay(wait);
  }
  cnt++;
}

// Slightly different, this makes the rainbow equally distributed throughout
int Pixels::rainbowCycle(uint8_t wait, uint8_t rerun) {
  if(cnt == rerun) {
    cnt = 0;
    return 0;
    //break;
  }
  uint16_t i, j;

  for(j=0; j<256; j++) { // 1 cycle of all colors on wheel
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
  cnt++;
}

//Theatre-style crawling lights with rainbow effect
int Pixels::theaterChaseRainbow(uint8_t wait, uint8_t rerun) {
  if(cnt == rerun) {
    cnt = 0;
    return 0;
    //break;
  }
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
  cnt++;
  

}

void Pixels::HW(){
  for(int shift=-53; shift<53;shift++){ 
      for(int i=0; i<53; i++) {
        for(int j=0; j<10; j++)  {
           if(helloWorld[j][i] == 1) 
           MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), RED);
           if(helloWorld[j][i] == 2) 
           MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), GREEN);
           if(helloWorld[j][i] == 3) 
           MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), BLUE);
           if(helloWorld[j][i] == 4) 
           MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), WHITE);
           if(helloWorld[j][i] == 5) 
           MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), PINK);
        }
      }
    MyLedMatrix::show();
    delay(75);
    MyLedMatrix::ClearScreen();
   } 
}

void Pixels::M(){
   for(int shift=-15; shift<12;shift++){ 
    for(int i=0; i<15; i++) {
      for(int j=0; j<10; j++)  {
         if(melie[j][i] == 1) 
         MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), RED);
         if(melie[j][i] == 2) 
         MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), GREEN);
         if(melie[j][i] == 3) 
         MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), BLUE);
         if(melie[j][i] == 4) 
         MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), WHITE);
         if(melie[j][i] == 5) 
         MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(i-shift,j), PINK);
      }
    }
  MyLedMatrix::show();
  delay(200);
  MyLedMatrix::ClearScreen();
 }  
}


void Pixels::dots(uint8_t wait, uint32_t color)
{
   byte array[m_numleds]; 
   byte counter=0; 
   byte randomNumber; 
   boolean inArray = false;
   // Do as long as all led values are written in the array
   while(counter < m_numleds) 
   {    
      randomNumber = random(0, m_numleds); 
      for(byte i=0; i<m_numleds-1; i++) 
      {
         if(array[i] == randomNumber)
         {
             inArray = true;
             break;
         }
         else
             inArray = false;
      }
      
      if(inArray == false)
      {
          array[counter] = randomNumber; 
          counter++; 
      }  
   } 
  // set all led numbers in the arry
  for(byte i=0; i<120; i++) {
    MyLedMatrix::setPixelColor(array[i], color);
    MyLedMatrix::show();
    delay(wait);
  }    
}

void Pixels::disband(uint8_t wait)
{
   dots(wait, 0);
}

void Pixels::appear(uint8_t wait, uint32_t color)
{
  dots(wait, color);
}

void Pixels::glow(uint32_t color, uint8_t wait)
{
  for(uint8_t brightness=0; brightness<64; brightness++){
    for(uint8_t led=0; led<m_numleds; led++){
      MyLedMatrix::setPixelColor(led, color);
      MyLedMatrix::setBrightness(brightness);
    }
  delay(10);
  MyLedMatrix::show();
  }
  MyLedMatrix::setBrightness(64);
 }

void Pixels::glowDispandMultiColor(uint8_t wait)
{
  glow(PINK);
  disband(wait);
  glow(ORANGE);
  disband(wait);
  glow(BLUE);
  disband(wait);
  glow(YELLOW);
  disband(wait);
  glow(RED);
  disband(wait);
}





