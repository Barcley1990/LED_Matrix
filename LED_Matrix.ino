/*
 * LED_Matrix.ino
 *
 * Created: 6/12/2015 11:12:24 AM
 * Author: Tobias Nuss
 */ 
 
#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
 
#define led11 0x00
#define led12 0x17
#include <avr/interrupt.h> 
#include <avr/io.h> 
#include <stdint.h>
#include <math.h> 


#include "Adafruit_NeoPixel.h"
#include "MyLedMatrix.h"
#include "Snake.h"
#include "Pixels.h"
#include "SpectrumAnalyzer.h"



// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(leds, pin, NEO_GRB + NEO_KHZ800);

#define quitButton O
char quitButton = 'O';

#define BRIGHTNESS 64

uint8_t height = 10;
uint8_t width = 12;
uint8_t pin = 4;
uint8_t leds = 120;

volatile uint8_t transmit_started = 0;
volatile uint8_t uart_timeout = 0;

#define statusLED 13
#define baudRate 19200


void setup() {
    // ADC for FFT
    adc_Setup();
 
    pinMode(statusLED, OUTPUT); 
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    // End of trinket special code
    
    Serial1.begin(baudRate);     
    Serial.begin(baudRate);
    
    MyLedMatrix *matrix = new MyLedMatrix(height, width, leds, pin, NEO_GRB + NEO_KHZ800);
    matrix->begin();
    matrix->show(); // Initialize all pixels to 'off'
    delete matrix;
    
    // Interrupt on Rx Pin 0
    attachInterrupt(digitalPinToInterrupt(0), RxInterrupt, CHANGE);
    
    Serial.println("--Bereit--");
    Serial1.println("--Bereit--"); 
    interrupts();
}
// end setup

int cnter=0;
int doOnce=0;
void loop(){
 
  // DO FFT (EQUALIZER)
  while(1) { // reduces jitter
   fft();
  }   
  

  
   // START OF PIXELFUNCTIONS
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
   // END OF PIXELFUNCTIONS

   blink(); 
}
 

	
void RxInterrupt() {
  if(Serial.available()) 
  {
    int incomingByte = Serial.read();
    if(incomingByte == 'X')
      Serial.println("OK!");
  } 
}


void blink() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}	



