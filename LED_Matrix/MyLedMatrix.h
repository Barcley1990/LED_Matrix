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
	
	void SetText();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	
	
	
private:
	uint8_t m_height;
	uint8_t m_width;
	uint8_t m_maxleds;


}; //MyLedMatrix

#endif //__MYLEDMATRIX_H__
