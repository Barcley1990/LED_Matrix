 /* 
* Pong.cpp
*
* Created: 24.07.2015 14:57:01
* Author: Tobias Nuss
*/


#include "Pong.h"
// __heap_start is declared in the linker script
extern unsigned char __heap_start;


// inherits from MyLedMatrix
// default constructor
Pong::Pong(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
	uint16_t momentan_frei = SP - (uint16_t) &__heap_start;	
	
  Serial.println("Pong->Constructor");
  Serial.println(" ");
  Serial.print("momentan_frei: "); Serial.println(momentan_frei);
  
  start = 4;
  m_width = w;
  m_height = h;
  Restart();
  DrawField();
  TimerSetup();
  
  m_ballX = 3;
  m_ballY = 3;
} 

Pong::~Pong()
{	 
  MyLedMatrix::ClearScreen();
  MyLedMatrix::show();
  Serial.println("Pong->Destructor");
  TIMSK1 &= ~(1 << TOIE1);
}



int Pong::Game()
{ 
  char inChar = (char)Serial.read();  
    if(inChar == 'R')  // up
      start--;
    if(inChar == 'L')  // down
      start++;
    if(inChar == 'O') { // exit
      Serial.println("Pong->Quit");
      Restart();
      return 0;
    }
  MyLedMatrix::ClearScreen();
  DrawField();
  ptr = &m_player[start];
  for(int i=0; i<3; i++) {
      Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_width-1, *ptr), RED);
      ptr++;
   }    
  Adafruit_NeoPixel::show();
    
  delay(500);
}

void Pong::DrawField() {
   for(uint8_t i=0; i<m_width; i++) {
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(i, 0), WHITE);
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(i, m_width-1), WHITE);
  }
  for(uint8_t i=0; i<m_height; i++) {
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(0, i), WHITE);
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_width-1, i), WHITE);
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(5, i), WHITE);
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(6, i), WHITE);
  }
  Adafruit_NeoPixel::show();
}

void Pong::UpdateBall() {
	Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_ballX, m_ballY, BLUE);
	
}


void Pong::Restart() {
  
}



int timer1_counter = 0;   // preload timer 65536-16MHz/256/2Hz
void Pong::TimerSetup()  // 16 bit Timer -> 2sec interrupt
{
  /*
  CSn2  CSn1  CSn0
  0     0     0    No clock source. (Timer/Counter stopped)
  0     0     1    clkI/O/1 (No prescaling
  0     1     0    clkI/O/8 (From prescaler)
  0     1     1    clkI/O/64 (From prescaler)
  1     0     0    clkI/O/256 (From prescaler)
  1     0     1    clkI/O/1024 (From prescaler)
  1     1     0    External clock source on Tn pin. Clock on falling edge
  1     1     1    External clock source on Tn pin. Clock on falling edge 
  */
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64886;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}


ISR(TIMER1_OVF_vect) 
{
  TCNT1 = timer1_counter;   // preload timer
  
  //Serial.println("I was here");
}
