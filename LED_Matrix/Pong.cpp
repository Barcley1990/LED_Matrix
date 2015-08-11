 /* 
* Pong.cpp
*
* Created: 24.07.2015 14:57:01
* Author: Tobias Nuss
*/


#include "Pong.h"


// inherits from MyLedMatrix
// default constructor
Pong::Pong(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
  Serial.println("Pong->Constructor");
  m_width = w;
  m_height = h;
  Restart();
  DrawField();
  TimerSetup();
  
  //ptr = &m_player[start];
} 

Pong::~Pong()
{
  Serial.println("Pong->Destructor");
  TIMSK1 &= ~(1 << TOIE1);
  cli();
}





int Pong::Game(){
  
  
  char inChar = (char)Serial.read();  
    if(inChar == 'R')  // up
     // start++;
    if(inChar == 'L')  // down
     // start--;
    if(inChar == 'O') { // exit
      Serial.println("Pong->Quit");
      Restart();
      return 0;
    }
  
  //*player_ptr = &m_player[start];
  for(int i=0; i<3; i++) {
      //Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(10, *player_ptr), RED);
     // player_ptr++;
   }  
   
    Adafruit_NeoPixel::show();
    
    delay(1000);
}

void Pong::DrawField() {
  m_field[2*m_width+2*m_height-4];
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
  // Set Player
  for(int i=0; i<3; i++) {
   // Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(10, *ptr), RED);
   // ptr++;
  }
  Adafruit_NeoPixel::show();
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
  
  Serial.println("I was here");
  //SpaceInvaders->Shot(void);
}
