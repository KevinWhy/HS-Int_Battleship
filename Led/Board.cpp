#include "Board.h"

// initialize board to all false

Board::board(int boardN){
  boardNumber = boardN;
  for(int i = 0; i < MAX_POS; i++){
    Pos[i].x = -1;
    Pos[i].y = -1;
    Pos[i].hitMarker = 0;
    Pos[i].ledState = false;
  }
}

int Board::getXPos(int posIndex){
  return Pos[posIndex].x;
}

int Board::getYPos(int posIndex){
  return Pos[posIndex].y;
}

int Board::getHMarker(int posIndex){
  return Pos[posIndex].hitMarker;
}

bool Board::getLedState(int posIndex){
  return Pos[posIndex].ledState;
}


// for the millis blinker
void Board::setLedState(int posIndex, bool state){
  Pos[posIndex].ledState = state;
}

void Board::setPos(Position passedInPos){
  if(numberOfPos < MAX_POS){
    Pos[numberOfPos].x = passedInPos.x;
    Pos[numberOfPos].y = passedInPos.y;
    Pos[numberOfPos].hitMarker = passedInPos.hitMarker;
  }
  numberOfPos++;
}

