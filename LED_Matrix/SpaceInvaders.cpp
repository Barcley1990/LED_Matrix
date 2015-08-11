/* 
* SpaceInvaders.cpp
*
* Created: 07.08.2015 21:41:01
* Author: Tobias Nuss
*/

#include "SpaceInvaders.h"


// inherits from MyLedMatrix
// default constructor
SpaceInvaders::SpaceInvaders(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
  m_quit = false;
  m_turn  = 0;
  m_maxleds = h*w;
  m_width = w;
  m_height = h;
  
  m_xAlt = m_xStart, m_xNeu = m_xStart;
  
  m_xStart = w;  // last row
  m_yStart = h/2;  // in middle of col
//  Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_xStart, m_yStart),155,155,0);  // pace spaceship
//  for(uint8_t i = 0; i<3*w; i++) {  // place invaders
//    uint32_t colour =  random(0,65000);    
//    Adafruit_NeoPixel::setPixelColor(i, colour);
//  }
//  Adafruit_NeoPixel::show();
  
  TimerSetup();  
} 

void SpaceInvaders::Restart(){
  for(uint8_t i = 0; i<m_maxleds; i++) {  // place invaders 
    Adafruit_NeoPixel::setPixelColor(i, 0);
  }
  Adafruit_NeoPixel::show(); 
}

void SpaceInvaders::MoveInvaders(){
}

void SpaceInvaders::MoveSpaceship(){
  m_xNeu = m_xStart + m_turn;
  m_xAlt = m_xNeu - m_turn ;   
  Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_xNeu, m_yStart), 155, 155, 0);
  Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_xAlt, m_yStart), 0);
  
  if(m_fire){
    m_bulletPos = m_width - 1;  // max y-1
    m_shotPos = m_xAlt;
    m_bullets++;
    m_fire = false;
  }
}

int SpaceInvaders::ReadSerial() {
  char inChar = (char)Serial.read();  
    if(inChar == 'R') { // rigth
      if(m_turn < 6)
          m_turn++;
    }
    if(inChar == 'L') { // left
      if(m_turn > -6)
        m_turn--;
    }
    if(inChar == 'X')  // fire
      m_fire = true;
    if(inChar == 'O') { // exit
      Restart();
      m_quit = true;
    }
}

void SpaceInvaders::Shot(){
  if (m_bullets>0){    
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_shotPos, --m_bulletPos), RED);// set new
    Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(m_shotPos, ++m_bulletPos), 0);// delete old
    m_bulletPos--;  // bullet to new position
  }
  if(m_bulletPos < 0)
    m_bullets--;      
}
  

int SpaceInvaders::Game()
{
  if(m_quit = true)
    return 0;
     
  ReadSerial();
  MoveSpaceship();
  MoveInvaders();
  Shot();

  delay(200);
  Adafruit_NeoPixel::show();

}





