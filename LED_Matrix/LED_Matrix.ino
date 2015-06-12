/*
 * LED_Matrix.ino
 *
 * Created: 6/12/2015 11:12:24 AM
 * Author: Tobias Nuss
 */ 

#include "Adafruit_NeoPixel.h"
#include "MyLedMatrix.h"

uint8_t height = 10;
uint8_t width = 12;
uint8_t pin = 4;
uint8_t leds = 12;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(leds, pin, NEO_GRB + NEO_KHZ800);
MyLedMatrix matrix = MyLedMatrix(height, width);

void setup()
{
	 // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
	 #if defined (__AVR_ATtiny85__)
	 if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	 #endif
	 // End of trinket special code


	 strip.begin();
	 strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
}
	
