/* 
* Sanke.h
*
* Created: 24.07.2015 14:57:01
* Author: Tobias Nuss
*/
#include <stdint.h>
#include "MyLedMatrix.h"


#ifndef __TETRIS_H__
#define __TETRIS_H__



class Tetris : public MyLedMatrix
{
public:
  Tetris(char qb, uint8_t h, uint8_t w, uint8_t l, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800);
  ~Tetris();
  void clearTrace();
  void updateCurrentMatrix();
  void displayFrame();
  void move(int moveDirection);
  void rotate();
  void convertToDeadBlock();
  void checkLinesCleared();
  void pauseGame();
  void restartGame();
  void checkUp();
  void startDropping();
  void checkLeft();
  void checkRight();
  void checkDrop();
  int Game();
  void gameOverFunc();
  
private:  
 //  Matrix Definition
#define cols         12
#define rows         10
#define leftLimit    0
#define rightLimit   11
#define topLimit     0
#define bottomLimit  9
int currentMatrix[rows][cols];

#define blank  { \
    {0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0}, \
}

//Tetris pieces: these piece matrices are represented by their corresponding colors (1-7)
#define Z1 { \
    {0, 0, 0, 0}, \
    {0, 0, 0, 0}, \
    {1, 1, 0, 0}, \
    {0, 1, 1, 0}, \
}
#define Z2 { \
    {0, 0, 0, 0}, \
    {0, 1, 0, 0}, \
    {1, 1, 0, 0}, \
    {1, 0, 0, 0}, \
}
#define S1 { \
    {0, 0, 0, 0}, \
    {0, 0, 0, 0}, \
    {0, 2, 2, 0}, \
    {2, 2, 0, 0}, \
}
#define S2 { \
    {0, 0, 0, 0}, \
    {2, 0, 0, 0}, \
    {2, 2, 0, 0}, \
    {0, 2, 0, 0}, \
}
#define J1 { \
    {0, 0, 0, 0}, \
    {0, 0, 0, 0}, \
    {3, 3, 3, 0}, \
    {0, 0, 3, 0}, \
}
#define J2 { \
    {0, 0, 0, 0}, \
    {0, 3, 0, 0}, \
    {0, 3, 0, 0}, \
    {3, 3, 0, 0}, \
}
#define J3 { \
    {0, 0, 0, 0}, \
    {3, 0, 0, 0}, \
    {3, 3, 3, 0}, \
    {0, 0, 0, 0}, \
}
#define J4 { \
    {0, 0, 0, 0}, \
    {0, 3, 3, 0}, \
    {0, 3, 0, 0}, \
    {0, 3, 0, 0}, \
}
#define L1 { \
    {0, 0, 0, 0}, \
    {0, 0, 0, 0}, \
    {4, 4, 4, 0}, \
    {4, 0, 0, 0}, \
}
#define L2 { \
    {0, 0, 0, 0}, \
    {4, 4, 0, 0}, \
    {0, 4, 0, 0}, \
    {0, 4, 0, 0}, \
}
#define L3 { \
    {0, 0, 0, 0}, \
    {0, 0, 4, 0}, \
    {4, 4, 4, 0}, \
    {0, 0, 0, 0}, \
}
#define L4 { \
    {0, 0, 0, 0}, \
    {0, 4, 0, 0}, \
    {0, 4, 0, 0}, \
    {0, 4, 4, 0}, \
}
#define T1 { \
    {0, 0, 0, 0}, \
    {0, 0, 0, 0}, \
    {6, 6, 6, 0}, \
    {0, 6, 0, 0}, \
}
#define T2 { \
    {0, 0, 0, 0}, \
    {0, 6, 0, 0}, \
    {6, 6, 0, 0}, \
    {0, 6, 0, 0}, \
}
#define T3 { \
    {0, 0, 0, 0}, \
    {0, 6, 0, 0}, \
    {6, 6, 6, 0}, \
    {0, 0, 0, 0}, \
}
#define T4 { \
    {0, 0, 0, 0}, \
    {0, 6, 0, 0}, \
    {0, 6, 6, 0}, \
    {0, 6, 0, 0}, \
}
#define I1 { \
    {0, 0, 0, 0}, \
    {0, 0, 0, 0}, \
    {5, 5, 5, 5}, \
    {0, 0, 0, 0}, \
}
#define I2 { \
    {0, 5, 0, 0}, \
    {0, 5, 0, 0}, \
    {0, 5, 0, 0}, \
    {0, 5, 0, 0}, \
}
#define O1 {  \
    {0, 0, 0, 0}, \
    {0, 0, 0, 0}, \
    {0, 7, 7, 0}, \
    {0, 7, 7, 0}, \
}


const byte gameOverLength = 9;
//byte gameOverLetters[gameOverLength][6][6]={G,A,M,E,O,V,E,R,blank};

//                      0,  1, 2,  3, 4,  5, 6,  7, 8, 9,10, 11,12,13,14, 15,16,17,18
byte pieces[19][4][4]={O1, Z1,Z2, S1,S2, I1,I2, J1,J2,J3,J4, L1,L2,L3,L4, T1,T2,T3,T4};
//                              0,  1,  2,  3,  4,  5,  6
byte piecesGenerated[7][4][4]={O1, Z1, S1, I1, J1, L1, T1};

byte currentPieceIndex;        // stores current piece index: from 0 to 18
byte currentPieceRotatedIndex; // stores the index of the rotated version of the current piece
byte currentPiece[4][4];       // stores the current piece matrix

//the top left corner of the current piece is tracked
int currentPieceRow;           // stores the row position of currentPiece[0][0]
int currentPieceCol;           // stores the col position of currentPiece[0][0]
int currentPieceMovedRow;      // stores the row position of currentPiece[0][0] after a certain move
int currentPieceMovedCol;      // stores the col position of currentPiece[0][0] after a certain move

byte numberOfLinesCleared;
boolean disableMove;
boolean pieceDropping;
byte textColor;
boolean gameRunning;
boolean gameOver;
boolean fastDrop;

boolean checkOverlapAndOutOfBoundary(byte pieceIndex) {
  int row=currentPieceMovedRow;
  int col=currentPieceMovedCol;
  for (int i=0;i<4;i++) {
    for (int j=0; j<4;j++) {
      if (pieces[pieceIndex][j][i]>0) {   // (row+j>-1 && row+j<rows)
        if (!( row+j<rows && (col+i>-1 && col+i<cols))) return true;  // checks out of boundary
        else if (currentMatrix[row+j][col+i]<0) return true;  // checks overlap
      }
    }
  }
  return false;
}

boolean checkIfLanded() {
  for (int i=0;i<4;i++) {
    for (int j=0; j<4;j++) {
      if ((currentPieceRow+j>-1 && currentPieceRow+j<rows) && (currentPieceCol+i>-1 && currentPieceCol+i<cols)) {
        if (currentMatrix[currentPieceRow+j][currentPieceCol+i]>0) {
          if (currentPieceRow+j==bottomLimit) return true;            // if the piece has dropped on the bottom
          else if (currentMatrix[currentPieceRow+j+1][currentPieceCol+i]<0) return true;  //if there is any deadblock just below the piece
        }
      }
    }
  }
  return false;
}

boolean generatePiece() {  //updates: currentPiece, currentMatrix, currentPieceRow, currentPieceCol, currentPieceIndex
//Serial.println("iwashere1");
  byte pieceIndex=random(7);
  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      currentPiece[j][i]=piecesGenerated[pieceIndex][j][i];
    }
  }
  for (int i=0; i<4; i++) {
    for (int j=0; j<2; j++) {
      if (piecesGenerated[pieceIndex][j+2][i]>0) {
        if (currentMatrix[j][i+2]<0) return false;
      }
    }
  }
  for (int i=0; i<4; i++) {
    for (int j=0; j<2; j++) {
      if (piecesGenerated[pieceIndex][j+2][i]>0) {
        currentMatrix[j][i+2]=piecesGenerated[pieceIndex][j+2][i];
      }
    }
  }
 // Serial.println("iwashere2");
  currentPieceRow = -2;
  currentPieceCol = 2;
 /// Serial.println(pieceIndex);
  switch (pieceIndex) {
   // Serial.println("iwashere4");
    case 0:
      currentPieceIndex=0;
      break;
    case 1:
      currentPieceIndex=1;
      break;
    case 2:
      currentPieceIndex=3;
      break;
    case 3:
      currentPieceIndex=5;
      break;
    case 4:
      currentPieceIndex=7;
      break;
    case 5:
      currentPieceIndex=11;
      break;
    case 6:
      currentPieceIndex=15;
      break;
  }
  //Serial.println("iwashere5");
  return true;
}
  
  
}; //Tetris




#endif //__TETRIS_H__



