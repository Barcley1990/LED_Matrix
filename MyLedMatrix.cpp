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
  Serial1.println("MyLedMatrix->Constructor");
	m_height = h;
	m_width = w;
	m_maxleds = m_height*m_width;
} 

MyLedMatrix::~MyLedMatrix()
{
  Serial1.println("MyLedMatrix->Destructor");
}

void MyLedMatrix::FillScreen(uint8_t r, uint8_t g, uint8_t b)
{
	for (int i=0; i<m_maxleds; i++)
	{
		Adafruit_NeoPixel::setPixelColor(i,r,g,b);
	}
        //Adafruit_NeoPixel::show();
}

void MyLedMatrix::ClearScreen()
{
	for (int i=0; i<m_maxleds; i++)
	{
		Adafruit_NeoPixel::setPixelColor(i,0,0,0);
	}
	//Adafruit_NeoPixel::show();
}

uint16_t MyLedMatrix::SetXY(uint8_t x, uint8_t y)
{
  uint16_t i;
  if(x>m_width-1) x = m_maxleds+1;//m_width-1;
  if(y>m_height-1) y = m_maxleds+1;//m_height-1;
  if(x<0) x = 0;
  if(y<0) y = 0;
  
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
/* X and Y are the  */
uint8_t MyLedMatrix::GetXY(uint16_t n, uint8_t *X, uint8_t *Y)
{
	if( (n/m_width)%2 & 0x01 )
	{
		// Odd rows run backwards
		*X = abs((n % m_width)-(m_width-1));
		*Y = abs((n % m_height)-(m_height-1));
	}	
	else
	{
		// Even rows run forwards
		*X = n % m_width;
		*Y = n % m_height;
	}
}


void MyLedMatrix::SetText(char *text, uint8_t r, uint8_t g, uint8_t b)
{
     for(uint8_t i=0; i<(strlen(text)*5); i++)
     {
       //char *ch = &text[i];
       SetChar(text[i], r ,g ,b, m_width-i, 0);
       Adafruit_NeoPixel::show();
       delay(100);
     }   
}

void MyLedMatrix::SetChar(char ch, uint8_t r, uint8_t g, uint8_t b, uint8_t offsetX, uint8_t offsetY)
{
    uint8_t i = ch*5;
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

void MyLedMatrix::MoveRight(uint8_t steps)
{
	uint8_t *pixels = Adafruit_NeoPixel::getPixels();	
	uint8_t shiftedX, shiftedY;
	uint16_t position;
	
	
	for (uint8_t i=0; i<m_maxleds; i++)
	{		
		// for debugging purpose only
		Serial1.print("pixels: ");
		Serial1.println(*pixels);
		Serial1.print("Position: ");
		Serial1.println(position);
		position = *pixels;
	
		uint8_t color = Adafruit_NeoPixel::getPixelColor(position);		
		Serial1.print("Color: ");
		Serial1.println(color);
		
		Adafruit_NeoPixel::resetPixel(position);	
		GetXY(position, &shiftedX, &shiftedY);
		Adafruit_NeoPixel::setPixelColor(SetXY(shiftedX+steps, shiftedY), color); 
		pixels++;
	}	
	Adafruit_NeoPixel::show();
}






















