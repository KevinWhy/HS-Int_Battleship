#include "Board.h"

// initialize board to all false

Board::board(){
  for(int i = 0; i < MAX_POS; i++){
    Pos[i].x = -1;
    Pos[i].y = -1;
    Pos[i].hitMarker = 0;
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



