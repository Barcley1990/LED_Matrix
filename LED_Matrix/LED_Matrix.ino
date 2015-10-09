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
uint8_t pin = 4;
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


void setup() {

   MyLedMatrix *matrix = new MyLedMatrix(height, width, leds, pin, NEO_GRB + NEO_KHZ800);
   
   pinMode(13, OUTPUT);
   
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    // End of trinket special code
    matrix->begin();
    matrix->show(); // Initialize all pixels to 'off'
    
    Serial1.begin(19200);     
    Serial.begin(19200);
    Serial.println("--Bereit--");
    Serial1.println("--Bereit--"); 
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
 
    
  
    delete matrix;
    matrix->show();

}
// end setup

int test=0;
int cnter;

void loop(){
  char inChar = (char)Serial1.read(); 
  if(inChar == 'X') {
    Snake* snake = new Snake(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
    while(snake->Game(200));
    delete snake;   
  }
   
   
  if(test==0){
    Pixels* once = new Pixels(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
    once->HW();   
    delete once;
    test=1;
  }
    
   Pixels* pixels = new Pixels(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
   pixels->glowDispandMultiColor();   
   while(pixels->Rainbow(10, 10));
   cnter = random(1,7);
   switch(cnter){
     case 1 : while(pixels->colorWipe(BLUE, 10));
       break;
     case 2 : while(pixels->colorWipe(RED, 10));
       break;
     case 3 : while(pixels->colorWipe(YELLOW, 10));
       break;
     case 4 : while(pixels->colorWipe(PINK, 10));
       break;
     case 5 : while(pixels->colorWipe(GREEN, 10));
       break;
     case 6 : while(pixels->colorWipe(ORANGE, 10));
       break;
     case 7 : while(pixels->colorWipe(WHITE, 10));
       break;
   }
   while(pixels->theaterChaseRainbow(20));
   delete pixels;
  

   blink();
   
  
}
 

	


void blink() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}	
