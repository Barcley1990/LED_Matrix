/* 
* Pong.cpp
*
* Created: 07.08.2015 21:41:01
* Author: Tobias Nuss
*/

#include <stdint.h>
#include "MyLedMatrix.h"


#ifndef __PONG_H__
#define __PONG_H__



class Pong : public MyLedMatrix
{
public:
  Pong(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);
  ~Pong();
  int Game();
  void Restart();
  void DrawField();
  void UpdateBall();
  
void TimerSetup();
private:
  uint8_t m_move, m_height, m_width, m_enemy, m_ledVal;


  int8_t start;
  uint8_t m_player[10] = {0,1,2,3,4,5,6,7,8,9};
  uint8_t *ptr;
  
  uint8_t m_ballX;
  uint8_t m_ballY;
  
}; //Pong




#endif //__PONG_H__
