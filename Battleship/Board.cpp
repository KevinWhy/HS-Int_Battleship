#include "Board.h"

unsigned long previousMillis = 0;
int interval = 100;

// initialize board to all false

Board::Board(int boardN){
  boardNumber = boardN;
  for(int i = 0; i < MAX_POS; i++){
      Pos[i].x = -1;
      Pos[i].y = -1;
      Pos[i].hitMarker = -1;
      //Pos[i].ledState = false;
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

/*bool Board::getLedState(int posIndex){
  return Pos[posIndex].ledState;
}*/

// for the millis blinker
/*id Board::setLedState(int posIndex, bool state){
  Pos[posIndex].ledState = state;
}*/

void Board::setPos(Position passedInPos){
  if(numberOfPos < MAX_POS){
    Pos[numberOfPos].x = passedInPos.x;
    Pos[numberOfPos].y = passedInPos.y;
    Pos[numberOfPos].hitMarker = 0;
    numberOfPos++;
  }
}
void Board::setMissPos(Position passedInPos){
  if(numberOfPos < MAX_POS){
    Pos[numberOfPos].x = passedInPos.x;
    Pos[numberOfPos].y = passedInPos.y;
    Pos[numberOfPos].hitMarker = passedInPos.hitMarker;
    numberOfPos++;
  }
}

void Board::printa(){    
  Serial.print(F("This is Board "));
  Serial.println(boardNumber);
  for(int i = 0; i < numberOfPos; ++i)
  {
    Serial.print(Pos[i].x, DEC);
    Serial.print(F(", "));
    Serial.print(Pos[i].y, DEC);
    Serial.print(F(", HM: "));
    Serial.println(Pos[i].hitMarker);
  }
}

// display function for board

// boardNumber+1 must be changed to boardNumber+2 in main code
void Board::display(LedControl lc){
  int i = 0;
  int j = 0;
  while(i < numberOfPos){
    if(Pos[i].hitMarker == 0){
      lc.setLed(boardNumber, Pos[i].x, Pos[i].y, true);
      
//    }else if(Pos[i].hitMarker == 1){
//      //Serial.println(F("we are here"));
//      if(millis() - previousMillis > interval) {
//        Pos[i].ledState = !Pos[i].ledState;
//        lc.setLed(boardNumber, Pos[i].x, Pos[i].y, Pos[i].ledState);
//        lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, Pos[i].ledState); // IMPORTANT: the boardNumber+2 is for displaying 0&2 and 1&3 together
//        previousMillis = millis();
//      }
    }else if(Pos[i].hitMarker == 2){
      lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, true);
    } 
    i++;
  }

  i = 0;

  if(millis() - previousMillis > interval) {
  ledS = !ledS;
    while(i < numberOfPos){
      if(Pos[i].hitMarker == 1){
        lc.setLed(boardNumber, Pos[i].x, Pos[i].y, ledS);
        lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, ledS); // IMPORTANT: the boardNumber+2 is for displaying 0&2 and 1&3 together
      }
      i++;
    }
  previousMillis = millis();
  }
//  if(millis() - previousMillis > interval) {
//     Pos[i].ledState = !Pos[i].ledState;
//     ledS = !ledS;
//     while(i < numberOfPos){
//       if(Pos[i].hitMarker == 1){
//          lc.setLed(boardNumber, Pos[i].x, Pos[i].y, ledS);
//          lc.setLed(boardNumber+1, Pos[i].x, Pos[i].y, ledS); // IMPORTANT: the boardNumber+2 is for displaying 0&2 and 1&3 together
//          i++;
//       }
//     }
//     previousMillis = millis();
//     
//  }
}


