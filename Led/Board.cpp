#include "Board.h"

unsigned long previousMillis = 0;
int interval = 100;

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
    numberOfPos++;
  }
}

// display function for board

// boardNumber+1 must be changed to boardNumber+2 in main code
void Board::display(LedControl lc){
  int i = 0;
  while(i < numberOfPos){
    if(Pos[i].hitMarker == 0){
      lc.setLed(boardNumber, Pos[i].x, Pos[i].y, true);
      
    }else if(Pos[i].hitMarker == 1){
      Serial.println("we are here");
      if(millis() - previousMillis > interval) {
        Pos[i].ledState = !Pos[i].ledState;
        lc.setLed(boardNumber, Pos[i].x, Pos[i].y, Pos[i].ledState);
        lc.setLed(boardNumber+2, Pos[i].x, Pos[i].y, Pos[i].ledState); // IMPORTANT: the boardNumber+2 is for displaying 0&2 and 1&3 together
        previousMillis = millis();
      } 
      
    }else if(Pos[i].hitMarker == 2){
      lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, true);
    } 
  i++;
  }
}


