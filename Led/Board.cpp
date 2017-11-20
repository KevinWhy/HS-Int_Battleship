#include "Board.h"

unsigned int previousMillis = 0;
int interval = 1000;

// initialize board to all false

Board::Board(int boardN){
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
    Pos[numberOfPos].hitMarker = 1;
    numberOfPos++;
  }
}

// display function for board
void Board::display(LedControl lc){
  int i = 0;
  while(i < numberOfPos){
    if(Pos[i].hitMarker == 0){
      lc.setLed(boardNumber, Pos[i].x, Pos[i].y, false);
      lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, true);
      
    }else if(Pos[i].hitMarker == 1){
      if(millis() - previousMillis > interval) {
        Pos[i].ledState = !Pos[i].ledState;
        lc.setLed(boardNumber, Pos[i].x, Pos[i].y, Pos[i].ledState);
        lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, Pos[i].ledState);
        previousMillis = millis();
      } 
      
    }else if(Pos[i].hitMarker == 2){
      lc.setLed(boardNumber, Pos[i].x, Pos[i].y, true);
      lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, false);
    } 
    i++;
  }
}


