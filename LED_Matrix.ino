/*
 * LED_Matrix.ino
 *
 * Created: 6/12/2015 11:12:24 AM
 * Author: Tobias Nuss
 */ 
#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

#include <FFT.h> // include the library
#include <avr/interrupt.h> 
#include <avr/io.h> 
#include <stdint.h>
#include <math.h> 

#include "Adafruit_NeoPixel.h"
#include "MyLedMatrix.h"
#include "Snake.h"
#include "Pixels.h"
#include "SpectrumAnalyzer.h"

#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
 
#define led11 0x00
#define led12 0x17
#define BRIGHTNESS 64
#define statusLED 13
#define baudRate 115200

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(leds, pin, NEO_GRB + NEO_KHZ800);

uint8_t height = 10;
uint8_t width = 12;
uint8_t pin = 4;
uint8_t leds = 120;

volatile uint8_t transmit_started = 0;
volatile uint8_t uart_timeout = 0;
#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
void setup() {
    //Serial1.begin(baudRate);     
    Serial.begin(baudRate);
    // Status LED to Output
    pinMode(statusLED, OUTPUT); 
    // ADC for FFT
    //adc_Setup();
    TIMSK0 = 0; // turn off timer0 for lower jitter
    ADCSRA = 0xe5; // set the adc to free running mode
    ADMUX = 0x40; // use adc0
    DIDR0 = 0x01; // turn off the digital input for adc0
   
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    // End of trinket special code
  
    MyLedMatrix *matrix = new MyLedMatrix(height, width, leds, pin, NEO_GRB + NEO_KHZ800);
    matrix->begin();
    matrix->show(); // Initialize all pixels to 'off'
    delete matrix;
    
    // Interrupt on Rx Pin 0
    //attachInterrupt(digitalPinToInterrupt(0), RxInterrupt, CHANGE);
    
    Serial.println("--Bereit--");
    Serial1.println("--Bereit--"); 
    interrupts();
}
// end setup

int cnter=0;
int doOnce=0;
void loop() {
  
   // DO FFT (EQUALIZER)
   doFFT();
   //blink(); 
   
 
    
    
    /*
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
*/ 

  
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
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}	

int aEqualizerArray[13];
int *pEqualizerPtr = aEqualizerArray;
void doFFT()
{  
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
        while(!(ADCSRA & 0x10)); // wait for adc to be ready
        ADCSRA = 0xf5; // restart adc
        byte m = ADCL; // fetch adc data
        byte j = ADCH;
        int k = (j << 8) | m; // form into an int
        k -= 0x0200; // form into a signed int
        k <<= 6; // form into a 16b signed int
        fft_input[i] = k; // put real data into even bins
        fft_input[i+1] = 0; // set odd bins to 0
    }   
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei();
    //Serial.println("start");
    for (byte i = 0 ; i < FFT_N/2 ; i++) { 
        Serial.println(fft_log_out[i]); // send out the data
        delay(100);
    }
    
/*    // Normalize -> 12 cols -> 12 frequencies
    byte i=0;
    while (i<FFT_N/2)
    {
      byte add;
      for (byte j=0; j<10; j++)
      {
        add += fft_log_out[j+i];
      }
      *pEqualizerPtr = add;
       pEqualizerPtr++; 
    i += 10;
    }
    pEqualizerPtr = aEqualizerArray;
    
    //MyLedMatrix *matrix = new MyLedMatrix(height, width, leds, pin, NEO_GRB + NEO_KHZ800);  
    //matrix->ClearScreen(); 
    for(byte x=0; x<12; x++)
    {
      for(byte y=0; y<10; y++)
      {
        float yPeak = aEqualizerArray[x];
        float test = (yPeak / 255) * 10;
        byte test2 = test;
        //Serial.print(x); Serial.print(", "); Serial.println(test2);

          //matrix->SetXY(x, test2, GREEN);
      }    
    }
    for (byte i = 0 ; i < 10 ; i++) { 
        Serial.println(aEqualizerArray[i]); // send out the data
        delay(100);
    }
    //matrix->show(); 
    //delete matrix;
    //delay(100);
*/    
}



