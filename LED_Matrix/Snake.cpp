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
  m_length = 0;
  m_feedX  = 5;
  m_feedY  = 5;
  m_turn = 0;
  
   
  
  
} 



uint8_t snakeOld[120];
uint8_t snakeNew[120];
uint8_t *pOld = snakeOld;
uint8_t *pNew = snakeNew;

int ledVal = 0;

void Snake::Game(uint8_t wait) {
  char inChar = (char)Serial1.read();  
    if(inChar == 'd')  // rigth
      m_turn++;
    if(inChar == 's')  // left
      m_turn--;
    

  if( (m_feedX==m_snakeX) && (m_feedY==m_snakeY) ) {  
    PlaceFood();
    pOld++;    
  }
    /* delete old snake */
    MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_snakeX, m_snakeY), 0, 0, 0);
    //MyLedMatrix::setPixelColor(life[0], 0, 0, 0);
   
    
    if(m_turn<0) m_turn = 3;  if(m_turn>3) m_turn = 0;
    switch(m_turn) {
      case 0 :  if(m_snakeX>=11) m_snakeX=-1;
                ledVal = MyLedMatrix::SetXY(++m_snakeX, m_snakeY); 
                *pOld = ledVal;
                //MyLedMatrix::setPixelColor(ledVal, 155, 0, 0);               
                break;
      case 1 :  if(m_snakeY>=9) m_snakeY=-1;
                ledVal = MyLedMatrix::SetXY(m_snakeX, ++m_snakeY); 
                *pOld = ledVal;
               // MyLedMatrix::setPixelColor(ledVal, 155, 0, 0);              
                break;
      case 2 :  if(m_snakeX<=0) m_snakeX=12;
                ledVal = MyLedMatrix::SetXY(--m_snakeX, m_snakeY);
                *pOld = ledVal;
                //MyLedMatrix::setPixelColor(ledVal, 155, 0, 0);              
                break;
      case 3 :  if(m_snakeY<=0) m_snakeY=10; 
                ledVal = MyLedMatrix::SetXY(m_snakeX, --m_snakeY);
                *pOld = ledVal;
                //MyLedMatrix::setPixelColor(ledVal, 155, 0, 0);            
                break;
    }
    delay(wait);
       

    MyLedMatrix::ClearScreen();
    
    for(int i=0; i<10; i++) {
      MyLedMatrix::setPixelColor(snakeOld[i], 155, 0, 0);
      snakeOld[i-1] = snakeOld[i];
    }    
    
    //Serial1.print("0: ");Serial1.print(snakeOld[0]);Serial1.print(", ");Serial1.print("1: ");Serial1.print(snakeOld[1]); Serial1.print(", ");
    //Serial1.print("2: ");Serial1.print(snakeOld[2]);Serial1.print(", ");Serial1.print("3: ");Serial1.println(snakeOld[3]);  
    
    MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX, m_feedY), 0, 155, 0);
    
    MyLedMatrix::show();
    
    

}

void Snake::PlaceFood(){
  m_feedX = random(0,11);
  m_feedY = random(0,9); 
  MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX,m_feedY), 0, 155, 0);
}

















