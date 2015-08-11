/* 
* SpaceInvaders.cpp
*
* Created: 07.08.2015 21:41:01
* Author: Tobias Nuss
*/

#include <stdint.h>
#include "MyLedMatrix.h"


#ifndef __SPACEINVADERS_H__
#define __SPACEINVADERS_H__



class SpaceInvaders : public MyLedMatrix
{
public:
  SpaceInvaders(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);
  void Restart();
  int ReadSerial();
  void MoveInvaders();
  void MoveSpaceship();
  void Shot();
  int Game();
  void TimerSetup();
  
private:
  bool m_quit;
  uint8_t m_maxleds;
  uint8_t m_width, m_height;
  uint8_t m_fire;
  int8_t m_turn;
  uint8_t m_xStart, m_yStart;
  uint8_t m_xAlt, m_xNeu;
  uint8_t m_bullets, m_bulletPos, m_shotPos;

}; //SpaceInvaders




#endif //__SPACEINVADERS_H__
