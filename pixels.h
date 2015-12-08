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
  void HW(void);
  void M(void);
  
  void dots(uint8_t wait, uint32_t color);
  void disband(uint8_t wait);
  void appear(uint8_t wait, uint32_t color);
  
  void glow(uint32_t c, uint8_t wait = 10);
  void glowDispandMultiColor(uint8_t wait = 10);
  
  char helloWorld[10][53] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,1,0,2,2,2,2,0,3,0,0,0,0,4,0,0,0,0,2,2,2,2,0,0,0,0,1,0,0,0,1,0,2,2,2,2,0,5,5,5,5,0,4,0,0,0,0,2,2,2,0},
        {1,0,0,1,0,2,0,0,0,0,3,0,0,0,0,4,0,0,0,0,2,0,0,2,0,0,0,0,1,0,0,0,1,0,2,0,0,2,0,5,0,0,5,0,4,0,0,0,0,2,0,0,2},
        {1,1,1,1,0,2,2,2,2,0,3,0,0,0,0,4,0,0,0,0,2,0,0,2,0,0,0,0,1,0,0,0,1,0,2,0,0,2,0,5,5,5,5,0,4,0,0,0,0,2,0,0,2},
        {1,0,0,1,0,2,0,0,0,0,3,0,0,0,0,4,0,0,0,0,2,0,0,2,0,0,0,0,1,0,1,0,1,0,2,0,0,2,0,5,0,5,0,0,4,0,0,0,0,2,0,0,2},
        {1,0,0,1,0,2,2,2,2,0,3,3,3,3,0,4,4,4,4,0,2,2,2,2,0,0,0,0,0,1,0,1,0,0,2,2,2,2,0,5,0,0,5,0,4,4,4,4,0,2,2,2,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };
  char melie[10][15] = {
    {2,2,0,2,2,3,3,3,4,0,0,5,3,3,3},
    {2,0,2,0,2,3,0,0,4,0,0,5,3,0,0},
    {2,0,0,0,2,3,3,3,4,0,0,5,3,3,3},
    {2,0,0,0,2,3,0,0,4,0,0,5,3,0,0},
    {2,0,0,0,2,3,3,3,4,4,4,5,3,3,3},
    {0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
    {0,0,1,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
  };

private:
  uint8_t m_height;
  uint8_t m_width;
  uint8_t m_maxleds;
  uint8_t m_numleds;
  char m_quitButton;


}; //Pixels




#endif //__PIXELS_H__


