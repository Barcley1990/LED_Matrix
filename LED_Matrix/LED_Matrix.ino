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
#include "SpaceInvaders.h"
#include "Pong.h"
#include "Tetris.h"

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
    while(!Serial);
    Serial1.println("--Bereit--"); 
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
  
/*  for(int i=0; i<10; i++) {
    matrix->SetChar(i,155,0,0,5,0);
    matrix->show();
    delay(200);
    matrix->ClearScreen();
    matrix->show();
  }
 */ 

/*   
 int currentMatrix[10][12] = {
      {0,0,0,0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1},
  };
  
  for(int i=0; i<12; i++) {
    for(int j=0; j<10; j++)  {
      if(currentMatrix[j][i] != 0) 
       matrix->setPixelColor(matrix->SetXY(i,j), RED);
    }
  }
  
  matrix->show();
 */
  delete matrix;
}
uint8_t n = 0;


void loop(){
  
  char inChar = (char)Serial1.read(); 
  if(inChar == 'X') {
    Snake* snake = new Snake(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
    while(snake->Game(200));
    delete snake;   
  }/*
  if(inChar == 'D') {
     Pong* pong = new Pong(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
     while(pong->Game());
     delete pong;
  }*//*
  if(inChar == 'S') {
     SpaceInvaders* spaceinvaders = new SpaceInvaders(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
     while(spaceinvaders->Game());
     delete spaceinvaders;
  }*/
  /*if(inChar == 'O') {
     Tetris* tetris = new Tetris(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
     while(tetris->Game());
     delete tetris;
  }*/
  if(inChar == '1') {
     Pixels* pixels = new Pixels(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
     while(pixels->Rainbow(20));
     delete pixels;
  }
   if(inChar == '2') {
     Pixels* pixels = new Pixels(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
     while(pixels->colorWipe(20, BLUE));
     delete pixels;
  }
   if(inChar == '3') {
     Pixels* pixels = new Pixels(quitButton, height, width, leds, pin, NEO_GRB + NEO_KHZ800);
     while(pixels->theaterChaseRainbow(20));
     delete pixels;
  }

   blink();
   
  
}
 

	


void blink() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}	
