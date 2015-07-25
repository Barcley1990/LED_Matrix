/* 
* Snake.cpp
*
* Created: 24.07.2015 14:57:01
* Author: Tobias Nuss
*/


#include "Snake.h"


// inherits from MyLedMatrix
// default constructor
Snake::Snake(uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
  m_snakeX = 0;
  m_snakeY = 0;	
  m_feedX  = 0;
  m_feedY  = 0;
  m_turn = 0;

} 

void Snake::Move(){
char inChar = (char)Serial1.read();  
  

   if(inChar == 'd'){
    Serial1.print(inChar);
      if(m_snakeX>=11) 
        m_snakeX=11;
      else
        m_snakeX++; 
      Serial1.print(m_snakeX); Serial1.print(","); Serial1.println(m_snakeY);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX,m_snakeY), 155, 0, 0);
      MyLedMatrix::show(); 
    }

if(inChar == 'a'){
    Serial1.print(inChar);
      if(m_snakeX<=0) 
        m_snakeX=0;
      else
        m_snakeX--; 
      Serial1.print(m_snakeX); Serial1.print(","); Serial1.println(m_snakeY);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX,m_snakeY), 155, 0, 0);
      MyLedMatrix::show();         
    }
 
    if(inChar == 'w'){
    Serial1.print(inChar);
      if(m_snakeY<=0) 
        m_snakeY=0;
      else
        m_snakeY--; 
      Serial1.print(m_snakeX); Serial1.print(","); Serial1.println(m_snakeY);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX,m_snakeY), 155, 0, 0);
      MyLedMatrix::show();         
    }

    if(inChar == 's'){
    Serial1.print(inChar);
      if(m_snakeY>=9) 
        m_snakeY=9;
      else
        m_snakeY++; 
      Serial1.print(m_snakeX); Serial1.print(","); Serial1.println(m_snakeY);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX,m_snakeY), 155, 0, 0);
      MyLedMatrix::show();         
    } 
}


void Snake::Game(uint8_t wait)
{
  char inChar = (char)Serial1.read();  
    if(inChar == 'd'){  // rigth
     m_turn++;
    }
    if(inChar == 's'){  // left
      m_turn--;
    }

  if( (m_feedX==m_snakeX) && (m_feedY==m_snakeY) )  
    PlaceFood();
  
  

    MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX, m_snakeY), 0, 0, 0);
    
    if(m_turn<0) m_turn=3;  if(m_turn>3) m_turn=0;
    if(m_turn == 0) {
      if(m_snakeX>=11) m_snakeX=-1;
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(++m_snakeX, m_snakeY), 155, 0, 0);
    }
    if(m_turn == 1) {
      if(m_snakeY>=9) m_snakeY=-1;
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX, ++m_snakeY), 155, 0, 0);
    }
    if(m_turn == 2) {
      if(m_snakeX<=0) m_snakeX=12;
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(--m_snakeX, m_snakeY), 155, 0, 0);
    }
    if(m_turn == 3) {
      if(m_snakeY<=0) m_snakeY=10;
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX, --m_snakeY), 155, 0, 0);
    }
    delay(wait);    
    MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX, m_feedY), 0, 155, 0);
    MyLedMatrix::show();
  

}

void Snake::PlaceFood(){
  m_feedX = random(0,11);
  m_feedY = random(0,9); 
  MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX,m_feedY), 0, 155, 0);
  MyLedMatrix::show();
}

















