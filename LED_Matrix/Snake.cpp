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
	
} 

void Snake::Move()
{
char inChar = (char)Serial1.read();  
  

   if(inChar == 'd'){
    Serial1.print(inChar);
      if(x>=11) 
        x=11;
      else
        x++; 
      Serial1.print(x); Serial1.print(","); Serial1.println(y);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(x,y), 155, 0, 0);
      MyLedMatrix::show(); 
    }

if(inChar == 'a'){
    Serial1.print(inChar);
      if(x<=0) 
        x=0;
      else
        x--; 
      Serial1.print(x); Serial1.print(","); Serial1.println(y);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(x,y), 155, 0, 0);
      MyLedMatrix::show();         
    }
 
    if(inChar == 'w'){
    Serial1.print(inChar);
      if(y<=0) 
        y=0;
      else
        y--; 
      Serial1.print(x); Serial1.print(","); Serial1.println(y);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(x,y), 155, 0, 0);
      MyLedMatrix::show();         
    }

    if(inChar == 's'){
    Serial1.print(inChar);
      if(y>=9) 
        y=9;
      else
        y++; 
      Serial1.print(x); Serial1.print(","); Serial1.println(y);
      MyLedMatrix::clear();
      MyLedMatrix::setPixelColor(MyLedMatrix::SetXY(x,y), 155, 0, 0);
      MyLedMatrix::show();         
    } 
    
 
  
}




















