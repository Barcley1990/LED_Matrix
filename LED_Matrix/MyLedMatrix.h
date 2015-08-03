 /* 
* MyLedMatrix.h
*
* Created: 12.06.2015 14:57:01
* Author: Tobias Nuss
*/
#include <stdint.h>
#include "Adafruit_NeoPixel.h"


#ifndef __MYLEDMATRIX_H__
#define __MYLEDMATRIX_H__

#define RED     Adafruit_NeoPixel::Color(255, 0, 0)
#define BLUE	Adafruit_NeoPixel::Color(0, 255, 0)
#define GREEN	Adafruit_NeoPixel::Color(0, 0, 255)
#define WHITE	Adafruit_NeoPixel::Color(255, 255, 255)

class MyLedMatrix : public Adafruit_NeoPixel
{
public:
	MyLedMatrix(uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);

	void Begin();
	void FillScreen(uint8_t r, uint8_t g, uint8_t b);
	void ClearScreen();
	
	void SetText(char *text, uint8_t r, uint8_t g, uint8_t b);
        void SetChar(char ch, uint8_t r, uint8_t g, uint8_t b, uint8_t offsetX, uint8_t OffsetY);
	void MoveRight(uint8_t steps);
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	uint16_t SetXY(uint8_t x, uint8_t y);
	uint8_t GetXY(uint16_t n, uint8_t *X, uint8_t *Y);

	
	
	
private:
	uint8_t m_height;
	uint8_t m_width;
	uint8_t m_maxleds;
        uint8_t m_matrix[12][10];


}; //MyLedMatrix

#endif //__MYLEDMATRIX_H__
