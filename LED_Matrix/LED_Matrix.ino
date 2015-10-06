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
 /*
   char helloWorld[10][53] = {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,0,0,1,0,2,2,2,2,0,3,0,0,0,0,4,0,0,0,0,2,2,2,2,0,0,0,0,1,0,0,0,1,0,2,2,2,2,0,5,5,5,5,0,4,0,0,0,0,2,2,2,0},
      {1,0,0,1,0,2,0,0,0,0,3,0,0,0,0,4,0,0,0,0,2,0,0,2,0,0,0,0,1,0,0,0,1,0,2,0,0,2,0,5,0,0,5,0,4,0,0,0,0,2,0,0,2},
      {1,1,1,1,0,2,2,2,2,0,3,0,0,0,0,4,0,0,0,0,2,0,0,2,0,0,0,0,1,0,0,0,1,0,2,0,0,2,0,5,5,5,5,0,4,0,0,0,0,2,0,0,2},
      {1,0,0,1,0,2,0,0,0,0,3,0,0,0,0,4,0,0,0,0,2,0,0,2,0,0,0,0,1,0,1,0,1,0,2,0,0,2,0,5,0,5,0,0,4,0,0,0,0,2,0,0,2},
      {1,0,0,1,0,2,2,2,2,0,3,3,3,3,0,4,4,4,4,0,2,2,2,2,0,0,0,0,0,1,0,1,0,0,2,2,2,2,0,5,0,0,5,0,4,4,4,4,0,2,2,2,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };
 for(int shift=-53; shift<53;shift++){ 
    for(int i=0; i<53; i++) {
      for(int j=0; j<10; j++)  {
         if(helloWorld[j][i] == 1) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), RED);
         if(helloWorld[j][i] == 2) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), GREEN);
         if(helloWorld[j][i] == 3) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), BLUE);
         if(helloWorld[j][i] == 4) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), WHITE);
         if(helloWorld[j][i] == 5) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), PINK);
      }
    }
  matrix->show();
  delay(200);
  matrix->ClearScreen();
 } 
  char melie[10][15] = {
      {2,2,0,2,2,3,3,3,4,0,0,5,3,3,3},
      {2,0,2,0,2,3,0,0,4,0,0,5,3,0,0},
      {2,0,0,0,2,3,3,3,4,0,0,5,3,3,3},
      {2,0,0,0,2,3,0,0,4,0,0,5,3,0,0},
      {2,0,0,0,2,3,3,3,4,4,4,5,3,3,3},
      {0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
      {0,0,1,0,0,1,0,0,1,0,0,0,0,0,0},
      {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
      {0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
  };
  for(int shift=-15; shift<12;shift++){ 
    for(int i=0; i<15; i++) {
      for(int j=0; j<10; j++)  {
         if(melie[j][i] == 1) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), RED);
         if(melie[j][i] == 2) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), GREEN);
         if(melie[j][i] == 3) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), BLUE);
         if(melie[j][i] == 4) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), WHITE);
         if(melie[j][i] == 5) 
         matrix->setPixelColor(matrix->SetXY(i-shift,j), PINK);
      }
    }
  matrix->show();
  delay(200);
  matrix->ClearScreen();
 } 
 */
  delete matrix;
  matrix->show();

}
// end setup



void loop(){
  
  char inChar = (char)Serial1.read(); 
  if(inChar == 'X') {
    Snake* snake = new Snake(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
    while(snake->Game(200));
    delete snake;   
   }
   Pixels* pixels = new Pixels(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
   while(pixels->Rainbow(20, 10));
   while(pixels->colorWipe(BLUE, 10));
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
