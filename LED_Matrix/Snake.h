 /* 
* Sanke.h
*
* Created: 24.07.2015 14:57:01
* Author: Tobias Nuss
*/
#include <stdint.h>
#include "MyLedMatrix.h"


#ifndef __SANKE_H__
#define __SNAKE_H__



class Snake : public MyLedMatrix
{
public:
  Snake(uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);
  void Move();
  void Game(uint8_t wait);
  void PlaceFood();

private:
  int m_snakeX;
  int m_snakeY;
  int m_feedX;
  int m_feedY;
  int m_turn;



}; //Snake

#endif //__SNAKE_H__
