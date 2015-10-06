/* 
* Tetris.cpp
*
* Created: 07.08.2015 21:41:01
* Author: Tobias Nuss
*/

#include "Tetris.h"

Tetris::Tetris(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t) : MyLedMatrix(h, w, l, p, t)
{
  Serial1.println("Tetris->Constructor");
  
  //  random seed for color selection, direction selection, and food+snakehead generation  
  //randomSeed(analogRead(A0));
  byte rand1=random(7);
  rand1=random(7);
  rand1=random(7);
  
  //initialize variables
  numberOfLinesCleared=0;
  gameRunning = true;
  gameOver = false;
  disableMove = false;
  fastDrop= false;
  
  generatePiece();
}

Tetris::~Tetris() {
  Serial1.println("Tetris->Destructor");
}

void Tetris::clearTrace() {
 // Serial.println("Tetris->clearTrace");
  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      if ((currentPieceRow+j>-1 && currentPieceRow+j<rows) && (currentPieceCol+i>-1 && currentPieceCol+i<cols)) {
        if (currentMatrix[currentPieceRow+j][currentPieceCol+i]>0) 
          currentMatrix[currentPieceRow+j][currentPieceCol+i]=0;
      }
    }
  }
}

void Tetris::updateCurrentMatrix() {
  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      if ((currentPieceRow+j>-1 && currentPieceRow+j<rows) && (currentPieceCol+i>-1 && currentPieceCol+i<cols)) {
        if (currentPiece[j][i]!=0) 
          currentMatrix[currentPieceRow+j][currentPieceCol+i]=currentPiece[j][i];
      }
    }
  }
}



void Tetris::move(int moveDirection) {  //updates: currentPieceRow, currentPieceCol, currentMatrix
  // moveDirection: 2-down; 3-left; 4-right
  if (moveDirection==2) {
    currentPieceMovedRow=currentPieceRow+1;
    currentPieceMovedCol=currentPieceCol;
  }
  else if (moveDirection==3) {
    currentPieceMovedRow=currentPieceRow;
    currentPieceMovedCol=currentPieceCol-1;
  }
  else if (moveDirection==4) {
    currentPieceMovedRow=currentPieceRow;
    currentPieceMovedCol=currentPieceCol+1;
  }
  // check if move is valid
  if (!checkOverlapAndOutOfBoundary(currentPieceIndex)) {
    clearTrace();
    currentPieceRow=currentPieceMovedRow;
    currentPieceCol=currentPieceMovedCol;
    updateCurrentMatrix();
  }
}

void Tetris::rotate() {  // updates: currentPieceRotatedIndex, currentPieceIndex, currentPiece, and currentMatrix
  // obtain the currentPieceRotatedIndex
  if (currentPieceIndex==0) return;
  else if (currentPieceIndex<3) currentPieceRotatedIndex=3-currentPieceIndex;
  else if (currentPieceIndex<5) currentPieceRotatedIndex=7-currentPieceIndex;
  else if (currentPieceIndex<7) currentPieceRotatedIndex=11-currentPieceIndex;
  else if ((currentPieceIndex % 4)==2) currentPieceRotatedIndex=currentPieceIndex-3;
  else currentPieceRotatedIndex=currentPieceIndex+1;
  
  currentPieceMovedRow=currentPieceRow;
  currentPieceMovedCol=currentPieceCol;
    
  // check if the rotation is valid 
  if (!checkOverlapAndOutOfBoundary(currentPieceRotatedIndex)) {
    clearTrace();
    currentPieceIndex=currentPieceRotatedIndex;
    for (int i=0;i<4;i++) {
      for (int j=0;j<4;j++) {
        currentPiece[j][i]=pieces[currentPieceRotatedIndex][j][i];
      }
    }
    updateCurrentMatrix();
  }
}



void Tetris::convertToDeadBlock() {
  for (int i=0;i<cols;i++) {
    for (int j=0;j<rows;j++) {
      if (currentMatrix[j][i]>0) {
        currentMatrix[j][i]=-currentMatrix[j][i];
      }
    }
  }
}

void Tetris::checkLinesCleared() {
  byte lineErased[rows];
  byte rowCounter=0;
  for (int j=0;j<rows;j++) {
    byte colCounter=0;
    for (int i=0;i<cols;i++) {
      if (currentMatrix[j][i]==0) {
        lineErased[j]=0;
        break;
      }
      else colCounter+=1;
    }
    if (colCounter==8) {
      lineErased[j]=1;
      rowCounter+=1;
    }  
  }
  
  if (rowCounter==0) return;  // if no lines are cleared
  
  int tempMatrix[rows-rowCounter][cols];
  byte rowCounter2=0;
  for (int j=0;j<rows;j++) {
    if (lineErased[j]==0) {
      for (int i=0;i<cols;i++) tempMatrix[rowCounter2][i]=currentMatrix[j][i]+0;
      rowCounter2+=1;
    }
  }
  for (int j=0;j<rowCounter;j++) {
    for (int i=0;i<cols;i++) {
      currentMatrix[j][i]=0;
    }
  }
  for (int j=0;j<rows-rowCounter;j++) {
    for (int i=0;i<cols;i++) {
      currentMatrix[j+rowCounter][i]=tempMatrix[j][i];
    }
  }
  numberOfLinesCleared+=rowCounter;
}

//  All Interrupt Functions Go Under Here
void Tetris::pauseGame() {
  Serial1.println("Tetris->Pause Game");
  delay(5);
  if ((char)Serial1.read() == 'D') {
    gameRunning = !gameRunning;
    //if (gameRunning) {digitalWrite(pauseMusic,LOW);}
    //else digitalWrite(pauseMusic,HIGH);
  }
}

void Tetris::restartGame() {
  Serial1.println("Tetris->Restart Game");
  delay(5);
  if ((char)Serial1.read() == 'O') {  //reinitialize all variables
    for (int i=0;i<cols;i++) {
      for (int j=0; j<rows; j++) currentMatrix[j][i]=0;
    }
    textColor=random(7)+1;
    numberOfLinesCleared=0;
    
    // reinitilize variables
    gameRunning=false;
    gameOver=false;
    disableMove=false;
    pieceDropping=false;
    fastDrop= false;
    generatePiece();
    //digitalWrite(restartMusic,HIGH); 
    //digitalWrite(pauseMusic,LOW);
  }
}

unsigned long lastButtonPressTime=millis();
unsigned long time= millis();
// 1-up; 2-down; 3-left; 4-right

void Tetris::checkUp() {
  time= millis();
  delay(1);
  if ((char)Serial1.read() == 'F' && time-lastButtonPressTime>110 && disableMove==false && gameRunning==true) {
    Serial1.println("Tetris->up");
    rotate();
    lastButtonPressTime=millis();
  }
}

void Tetris::startDropping() {
  time = millis();
  if ((char)Serial1.read() == 'B' && time-lastButtonPressTime>110 && disableMove==false && gameRunning==true) {
    Serial1.println("Tetris->sd");
    pieceDropping=true;
    lastButtonPressTime=millis();
  }
}

void Tetris::checkLeft()  {
  time= millis();
  delay(1);
  if ((char)Serial.read() == 'L' && time-lastButtonPressTime>110 && disableMove==false && gameRunning==true) {
    Serial.println("Tetris->left");
    move(3);
    lastButtonPressTime=millis();
  }
}

void Tetris::checkRight() {  
  time= millis();
  delay(1);
  if ((char)Serial1.read() == 'R' && time-lastButtonPressTime>110 && disableMove==false && gameRunning==true) {
    Serial1.println("Tetris->right");
    move(4);
    lastButtonPressTime=millis();
  }
}

void Tetris::checkDrop() {  
  time= millis();
  delay(1);
  if ((char)Serial1.read() == 'X' && time-lastButtonPressTime>110 && disableMove==false && gameRunning==true) {
    Serial1.println("Tetris->drop");
    fastDrop=true;
    lastButtonPressTime=millis();
  }
}
  
  
//  used in the main loop to calculate the time interval between moves
unsigned long lastMoveTime=millis();
unsigned long currentMoveTime=millis();

unsigned long lastLandedTime=millis();
unsigned long currentLandedTime=millis();
   
int Tetris::Game() {
 // Serial.println("Tetris->washere");
  if ((char)Serial1.read() == 'O') {
    Serial1.println("Tetris->Quit");
    return 0;
  }
  checkUp();
  startDropping();
  checkLeft();
  checkRight();
  checkDrop();
  generatePiece();
  
  if (gameRunning==false) {
    displayFrame();
    //Serial.println("Tetris->gr=false");
  }
  else 
  {
    //Serial.println("Tetris->gr=true");
    //digitalWrite(restartMusic,LOW);
    displayFrame();
    currentMoveTime=millis();
    if (fastDrop==true) {
      while (!checkIfLanded()) move(2);
      displayFrame();
      fastDrop=false;
    }
    if ((char)Serial1.read() == 'B') pieceDropping=false;
    int timeInterval;
    if (!pieceDropping) timeInterval = 800-numberOfLinesCleared*10;
    else timeInterval= 120;
    if (!checkIfLanded() && currentMoveTime-lastMoveTime>timeInterval) {
      move(2);
      lastMoveTime=millis();
    }
    else if (checkIfLanded()) {
      lastLandedTime=millis();
      while (currentLandedTime<lastLandedTime+400) {
        currentLandedTime=millis();
        displayFrame();
      }
      if (!checkIfLanded()) int b;
      else {
        disableMove = true;
        convertToDeadBlock();
        checkLinesCleared();
        Serial1.println("Tetris->generatePiece");
        if (generatePiece()==false) {
          gameOverFunc();
          //displayTextOverlay(0);
        }
        else disableMove=false;
      }
    }
  }
  return 1;
  
}


void Tetris::gameOverFunc() {
  Serial1.println("Tetris->Game Over");
  gameRunning = false;
  gameOver =true;
  //digitalWrite(restartMusic,HIGH);
}
/*
byte gameOverMatrix[6][6*gameOverLength+7];

void conbineLetters(int index) {
  if (index==0) {  // gameOverLetters[9][6][6]={G,A,M,E,O,V,E,R,blank};
    for (int n=0; n<gameOverLength;n++) {
      for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
          gameOverMatrix[j][i+6*n]=gameOverLetters[n][j][i];
          if (n==0) gameOverMatrix[j][6*gameOverLength+i]=gameOverLetters[n][j][i];
          if (n==1 && i<1) gameOverMatrix[j][6*(gameOverLength+1)+i]=gameOverLetters[n][j][i];
        }
      }
    }
  }
}
*/ 
void Tetris::displayFrame() {
  //Serial.println("Tetris->Disp");
  byte color;
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++)  {
      if(currentMatrix[j][i] != 0) 
        Adafruit_NeoPixel::setPixelColor(MyLedMatrix::SetXY(i,j), RED);
    }
  }
  
  Adafruit_NeoPixel::show();
}












