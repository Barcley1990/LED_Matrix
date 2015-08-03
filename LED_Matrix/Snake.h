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
  Snake(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);
  void Restart();
  void Move();
  int Game(uint8_t wait);
  void PlaceFood();
  void GameCounter();
  
  uint8_t snakeOld[120];
  uint8_t *pOld = snakeOld;
  int ledVal = 0;

private:
  uint8_t m_snakeX;
  uint8_t m_snakeY;
  uint8_t m_length;
  uint8_t m_feedX;
  uint8_t m_feedY;
  int8_t m_turn;
  char m_quitButton;
  uint8_t m_gameCounter;
  uint8_t m_firstDigit;
  uint8_t m_secondDigit;
  uint8_t m_thirdDigit;

}; //Snake




#endif //__SNAKE_H__



