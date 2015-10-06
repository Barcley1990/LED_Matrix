/* 
* PIXELS.h
*
* Created: 01.08.2015 19:57:01
* Author: Tobias Nuss
*/
#include <stdint.h>
#include "MyLedMatrix.h"


#ifndef __PIXELS_H__
#define __PIXELS_H__



class Pixels : public MyLedMatrix
{
public:
  Pixels(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);
  uint32_t Wheel(byte WheelPos);
  int Rainbow(uint8_t wait, uint8_t rerun = 1);  
  int colorWipe(uint32_t c, uint8_t wait, uint8_t rerun = 1);
  int rainbowCycle(uint8_t wait, uint8_t rerun = 1);
  int theaterChaseRainbow(uint8_t wait, uint8_t rerun = 1);


private:
  uint8_t m_height;
  uint8_t m_width;
  uint8_t m_maxleds;
  char m_quitButton;


}; //Pixels




#endif //__PIXELS_H__



