#include "Abstract.h"

// IMPORTANT
// CODE is not tested but the logic should is there
// TO be put in main and used by Ritesh

// This function is used to check the game losing state by passing in the
// players ships states, if all the ship states are sunk then 
// returns true for that player LOSING

// to be put in Main.ino


bool playerLose(Ship ship1, Ship ship2, Ship ship3){
  bool lose = false;
  if(ship1.getShipState() == false){
    if(ship2.getShipState() == false){
      if(ship3.getShipState() == false){
         lose = true;
      }
    }
  }
  return lose;
}


// Check the coordinates with the board to see if there is already a position
// returns true if there is a matching coordinate

bool checkCoordinateInBoard(int x, int y, Board* tempBoard){
  for(int i=0; i < tempBoard->getNumberOfPos(); i++){
    if(x == tempBoard->Pos[i].x && y == tempBoard->Pos[i].y){
      return true;
    }
  }
  return false;
}

// This function is used to check if a shot position hits the ships position
// returns true if it hits a ship
// also updates the board and ships position hit marker

// takes in coordinate, board address, and ship address

//to be put in Main.ino

bool checkHit(int row, int col, Board* tempBoard, Ship* ship1, Ship* ship2, Ship* ship3){

  for(int i = 0; i < tempBoard->getNumberOfPos(); i++){
  
    if(tempBoard->Pos[i].hitMarker != 2)
    if(row == tempBoard->getXPos(i)){
      if(col == tempBoard->getYPos(i)){
        tempBoard->Pos[i].hitMarker = 1;

        // Change ship pos hitMarker as well;
        for(int i = 0; i < ship1->getSize();i++){
          if(row == ship1->Pos[i].x && col == ship1->Pos[i].y){
            ship1->Pos[i].hitMarker = 1;
          }
        }

        for(int i = 0; i < ship2->getSize();i++){
          if(row == ship2->Pos[i].x && col == ship2->Pos[i].y){
            ship2->Pos[i].hitMarker = 1;
          }
        }

        for(int i = 0; i < ship3->getSize();i++){
          if(row == ship3->Pos[i].x && col == ship3->Pos[i].y){
            ship3->Pos[i].hitMarker = 1;
          }
        }
      }
    }
  }
  // adds a position in the Pos array and updates the array size
  if(!checkCoordinateInBoard(row, col, tempBoard)){
    Position tempPos;
    tempPos.x = row;
    tempPos.y = col;
    tempPos.hitMarker = 2;
    tempBoard->setPos(tempPos);
  }
}

