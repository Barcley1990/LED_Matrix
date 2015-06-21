/* 
* MyLedMatrix.cpp
*
* Created: 12.06.2015 14:57:01
* Author: Tobias Nuss
*/


#include "MyLedMatrix.h"
#include "font8x8_basic.h"
// inherits from Adafruit_NeoPixel
// default constructor
MyLedMatrix::MyLedMatrix(uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : Adafruit_NeoPixel(l, p, t)
{
	m_height = h;
	m_width = w;
	m_maxleds = m_height*m_width;
} 

void MyLedMatrix::FillScreen(uint8_t r, uint8_t g, uint8_t b)
{
	for (int i=0; i<m_maxleds; i++)
	{
		Adafruit_NeoPixel::setPixelColor(i,r,g,b);
	}
        Adafruit_NeoPixel::show();
}

void MyLedMatrix::ClearScreen()
{
	for (int i=0; i<m_maxleds; i++)
	{
		Adafruit_NeoPixel::setPixelColor(i,0,0,0);
	}
	Adafruit_NeoPixel::show();
}

uint16_t MyLedMatrix::SetXY(uint8_t x, uint8_t y)
{
  uint16_t i;
  
     if( y & 0x01) 
     {
      // Odd rows run backwards
      uint8_t reverseX = (m_width - 1) - x;
      i = (y * m_width) + reverseX;
    } 
    else 
    {
      // Even rows run forwards
      i = (y * m_width) + x;
    }
    
    return i;    
}



void MyLedMatrix::SetText(char *text, uint8_t r, uint8_t g, uint8_t b)
{
     for(uint8_t i=0; i<strlen(text); i++)
     {
       char *ch = &text[i];
       SetChar(*ch, r ,g ,b, m_width-i, 0);
       delay(100);
     }   
}

void MyLedMatrix::SetChar(char ch, uint8_t r, uint8_t g, uint8_t b, uint8_t offsetX, uint8_t offsetY)
{
    uint8_t i = ch*3;
    char *ptr = &font[i+1];

    for(uint8_t x=0; x<=2; x++)
    {
       for(uint8_t y=0; y<=7; y++)
       {
         if(*ptr & (1<<y) )
         {       
           Adafruit_NeoPixel::setPixelColor(SetXY(x+offsetX, y+offsetY), r, g, b);
         }
       }
       ptr++;
    }
}





















