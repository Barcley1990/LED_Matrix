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
  Restart();
} 

void Snake::Restart()
{
   m_snakeX = 0;
   m_snakeY = 0;	
   m_feedX  = 5;
   m_feedY  = 5;
   m_turn = 0;
   for(int i=0; i<120; i++) {
    snakeOld[i] = -1; 
   }
   pOld = snakeOld;  
}

int Snake::Game(uint8_t wait) {
  char inChar = (char)Serial1.read();  
    if(inChar == 'R')  // rigth
      m_turn++;
    if(inChar == 'L')  // left
      m_turn--;
    if(inChar == 'X')  // exit
      return 0;

  MyLedMatrix::ClearScreen();
  
  /* found some food? */
  if( (m_feedX==m_snakeX) && (m_feedY==m_snakeY) ) {  
    PlaceFood();
    pOld++;    
  }
   
    if(m_turn<0) m_turn = 3;  if(m_turn>3) m_turn = 0;
    switch(m_turn) {
      case 0 :  if(m_snakeX>=11) m_snakeX=-1;
                ledVal = MyLedMatrix::SetXY(++m_snakeX, m_snakeY); 
                break;
      case 1 :  if(m_snakeY>=9) m_snakeY=-1;
                ledVal = MyLedMatrix::SetXY(m_snakeX, ++m_snakeY);            
                break;
      case 2 :  if(m_snakeX<=0) m_snakeX=12;
                ledVal = MyLedMatrix::SetXY(--m_snakeX, m_snakeY);             
                break;
      case 3 :  if(m_snakeY<=0) m_snakeY=10; 
                ledVal = MyLedMatrix::SetXY(m_snakeX, --m_snakeY);       
                break;
    }
   
    /* am I crashed? */   
    for(int j = 120; j>=0; j--){
        if(ledVal == snakeOld[j]) {
          Serial1.println("crash!!!");
          while((char)Serial1.read() != 'X') {
            MyLedMatrix::setPixelColor(ledVal, 0, 0, 155);
            for(int i=0; i<120; i++) {
              snakeOld[i-1] = snakeOld[i];
              MyLedMatrix::setPixelColor(snakeOld[i], 155, 0, 0);
            }  
            MyLedMatrix::show();
            delay(100);
            MyLedMatrix::setPixelColor(ledVal, 0, 0, 0);
            MyLedMatrix::show();
            delay(100);
          }
          MyLedMatrix::ClearScreen();
          MyLedMatrix::show();
          Restart();
          return 0;
        }
    } 
    /* write to array snakeOld */
    *pOld = ledVal; 
   
    
    for(int i=0; i<120; i++) {
      snakeOld[i-1] = snakeOld[i];
      MyLedMatrix::setPixelColor(snakeOld[i], 155, 0, 0);
    }  
     
    MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX, m_feedY), 0, 155, 0);
    MyLedMatrix::show();
       
    delay(wait);
    

}

void Snake::PlaceFood(){
  m_feedX = random(0,11);
  m_feedY = random(0,9); 
  MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(m_feedX,m_feedY), 0, 155, 0);
}

















