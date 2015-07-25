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
    if(inChar == 'd'){
     m_turn++;
    }
    if(inChar == 's'){
      m_turn--;
    }
  Serial1.println(m_turn);   
  if( (m_feedX==m_snakeX) && (m_feedY==m_snakeY) )  
    PlaceFood();
  
 // if(m_snakeX>=11) m_snakeX=0;
 // if(m_snakeY>=9) m_snakeY=0;
 // if(m_snakeX<=0) m_snakeX=11;
  //if(m_snakeY<=0) m_snakeY=9;
  
  

    MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX, m_snakeY), 0, 0, 0);
    
    if(m_turn == 0) {
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX, m_feedY), 0, 155, 0);
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(++m_snakeX, m_snakeY), 155, 0, 0);
      MyLedMatrix::show();
      delay(wait);
    }
    if(m_turn == 1) {
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX, m_feedY), 0, 155, 0);
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX, ++m_snakeY), 155, 0, 0);
      MyLedMatrix::show();
      delay(wait);
    }
    if(m_turn == 2) {
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX, m_feedY), 0, 155, 0);
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(--m_snakeX, m_snakeY), 155, 0, 0);
      MyLedMatrix::show();
      delay(wait);
    }
    if(m_turn == 3) {
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX, m_feedY), 0, 155, 0);
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX, --m_snakeY), 155, 0, 0);
      MyLedMatrix::show();
      delay(wait);
    }
    if(m_turn>3){
      m_turn=0;
      delay(wait);
    }
    if(m_turn<0){
      m_turn=3ssd;
      delay(wait);
    }
    
  

}

void Snake::PlaceFood(){
  m_feedX = random(0,11);
  m_feedY = random(0,9); 
  MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX,m_feedY), 0, 155, 0);
  MyLedMatrix::show();
}

















