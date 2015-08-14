/* 
* Sanke.h
*
* Created: 24.07.2015 14:57:01
* Author: Tobias Nuss
*/
#include <stdint.h>
#include "MyLedMatrix.h"


#ifndef __TETRIS_H__
#define __TETRIS_H__



class Tetris : public MyLedMatrix
{
public:
  Tetris(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);
  ~Tetris();
  void clearTrace();
  void updateCurrentMatrix();
  void displayFrame();
  void move(int moveDirection);
  void rotate();
  void convertToDeadBlock();
  void checkLinesCleared();
  void pauseGame();
  void restartGame();
  void checkUp();
  void startDropping();
  void checkLeft();
  void checkRight();
  void checkDrop();
  int Game();
  void gameOverFunc();
  
  

 
  
  
}; //Tetris




#endif //__TETRIS_H__



