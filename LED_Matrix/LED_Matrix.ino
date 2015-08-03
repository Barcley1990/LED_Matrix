/*
 * LED_Matrix.ino
 *
 * Created: 6/12/2015 11:12:24 AM
 * Author: Tobias Nuss
 */ 
#define led11 0x00
#define led12 0x17

#include <stdint.h>
#include <math.h> 
#include "Adafruit_NeoPixel.h"
#include "MyLedMatrix.h"
#include "Snake.h"
#include "Pixels.h"

#define quitButton O
char quitButton = 'O';

#define BRIGHTNESS 64

uint8_t height = 10;
uint8_t width = 12;
uint8_t pin = 5;
uint8_t leds = 120;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
volatile uint8_t transmit_started = 0;
volatile uint8_t uart_timeout = 0;



// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(leds, pin, NEO_GRB + NEO_KHZ800);

MyLedMatrix matrix = MyLedMatrix(height, width, leds, pin, NEO_GRB + NEO_KHZ800);
Snake snake =  Snake(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
Pixels pixels = Pixels(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);




void setup() {
   pinMode(13, OUTPUT);
   
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    // End of trinket special code
    matrix.begin();
    matrix.show(); // Initialize all pixels to 'off'
    Serial1.begin(19200);     
    //while(!Serial1);
    //Serial.begin(9600);
    
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
  
  for(int i=0; i<10; i++) {
    matrix.SetChar(i,155,0,0,5,0);
    matrix.show();
    delay(200);
    matrix.ClearScreen();
    matrix.show();
  }
    
}
uint8_t n = 0;

void loop(){
  
  char inChar = (char)Serial1.read();
  if(inChar == 'X')
    while(snake.Game(1000));
  if(inChar == '1')
    while(pixels.Rainbow(20));
  if(inChar == '2')
    while(pixels.colorWipe(20, BLUE));
  if(inChar == '3')
    while(pixels.rainbowCycle(20));  
  if(inChar == '4')
    while(pixels.theaterChaseRainbow(20));  

   matrix.ClearScreen();
   matrix.show();
   blink();
   
  
}
 

void serialEvent()
{
	while(Serial1.available())
	{                                
		transmit_started = true;
		// get the new byte:
		char inChar = (char)Serial1.read();
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n' || inChar == '\r')
		{
			stringComplete = true;
			uart_timeout = 0;
			transmit_started = false;
		 }
	}
}

void blink() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}	
