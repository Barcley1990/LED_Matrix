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


class MyLedMatrix : public Adafruit_NeoPixel
{
public:
	MyLedMatrix(uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);

	void Begin();
	void FillScreen(uint8_t r, uint8_t g, uint8_t b);
	void ClearScreen();
	
	void SetText(char *text, uint8_t r, uint8_t g, uint8_t b);
        void SetChar(char ch, uint8_t r, uint8_t g, uint8_t b, uint8_t offsetX, uint8_t OffsetY);
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
        uint16_t SetXY(uint8_t x, uint8_t y);

	
	
	
private:
	uint8_t m_height;
	uint8_t m_width;
	uint8_t m_maxleds;
        uint8_t m_matrix[12][10];


}; //MyLedMatrix

#endif //__MYLEDMATRIX_H__
