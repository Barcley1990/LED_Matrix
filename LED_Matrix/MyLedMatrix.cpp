/* 
* MyLedMatrix.cpp
*
* Created: 12.06.2015 14:57:01
* Author: Tobias Nuss
*/


#include "MyLedMatrix.h"
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
		Adafruit_NeoPixel::show();
	}
}

void MyLedMatrix::ClearScreen()
{
	for (int i=0; i<m_maxleds; i++)
	{
		Adafruit_NeoPixel::setPixelColor(i,0,0,0);
	}
	Adafruit_NeoPixel::show();
}