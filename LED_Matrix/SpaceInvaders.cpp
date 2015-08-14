/* 
* SpaceInvaders.cpp
*
* Created: 07.08.2015 21:41:01
* Author: Tobias Nuss
*/

#include "SpaceInvaders.h"

struct spaceShip{ 
       int x; 
       int y; 
       int shootcnt; 
       int shoot; 
}ship; 

struct bullet{ 
       int x; 
       int y; 
}bullet1, bullet2; 

// inherits from MyLedMatrix
// default constructor
SpaceInvaders::SpaceInvaders(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
  Serial.println("SpaceInvaders->Constructor");
  m_xSpaceShip  = 6;
  m_ySpaceShip = 9;
  ship.x = 6;
  ship.y = 9;
  m_maxleds = h*w;
  m_width = w;
  m_height = h;
} 

SpaceInvaders::~SpaceInvaders() {
  Serial.println("SpaceInvaders->Destructor");
}




void SpaceInvaders::Restart(){
  for(uint8_t i = 0; i<m_maxleds; i++) {  // place invaders 
    Adafruit_NeoPixel::setPixelColor(i, 0);
  }
  Adafruit_NeoPixel::show(); 
}

void SpaceInvaders::MoveInvaders(){
  for(uint8_t i = 0; i<3*m_width; i++) {  // place invaders
    uint32_t colour =  random(0,16581375);    
    Adafruit_NeoPixel::setPixelColor(i, colour);
  }  
}

void SpaceInvaders::MoveSpaceship(){ 
  Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(ship.x, ship.y), 155, 155, 0);

  m_xOldSsPos = ship.x;
  if(ship.shoot){    
     ship.shootcnt++; 
     if(ship.shootcnt = 1) { bullet1.y = 9; bullet1.x = ship.x; ship.shoot = false; }
     if(ship.shootcnt = 2) { bullet2.y = 9; bullet2.x = ship.x; ship.shoot = false; }
  }
}



void SpaceInvaders::Shot(){
  
 if(ship.shootcnt>0){
            Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(bullet1.x, --bullet1.y), RED);// set new
            Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(bullet1.x, ++bullet1.y), 0);// delete old
            bullet1.y--;  // bullet to new position
             
            Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(bullet2.x, --bullet2.y), RED);// set new
            Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(bullet2.x, ++bullet2.y), 0);// delete old
            bullet2.y--;  // bullet to new position
             

    
  }

     
}
  

int SpaceInvaders::Game()
{ 
  MyLedMatrix::ClearScreen();
  char inChar = (char)Serial.read();  
      if(inChar == 'R') { // rigth
        if(ship.x < 11)
            ship.x++;
      }
      if(inChar == 'L') { // left
        if(ship.x > 0)
          ship.x--;
      }
      if(inChar == 'X')  // fire
        ship.shoot = true;
      if(inChar == 'O') { // exit
        Serial.println("SpaceInvaders->Quit");
        Restart();
        return 0;
      }  
  //ReadSerial();
  Shot();
  MoveSpaceship();
  MoveInvaders();
  

  delay(200);
  Adafruit_NeoPixel::show();

}





