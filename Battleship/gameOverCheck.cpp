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
    if(x == tempBoard->getXPos(i) && y == tempBoard->getYPos(i)){
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

    bool value = false;
    int hold = 0;
   
  for(int i = 0; i < tempBoard->getNumberOfPos(); i++){

  /*
    Serial.print(tempBoard->Pos[i].x);
    Serial.print(F(", "));
    Serial.println(tempBoard->Pos[i].y);
    Serial.println(tempBoard->Pos[i].hitMarker);
    */
    if(tempBoard->Pos[i].hitMarker != 2 && tempBoard->Pos[i].hitMarker != 1)
    {
        
        if(col == tempBoard->getXPos(i)){
          if(row == tempBoard->getYPos(i)){
            //Serial.println(F("we came in"));
            value = true;
            hold = i;
            tempBoard->Pos[i].hitMarker = 1;
            

            // Change ship pos hitMarker as well;
            for(int i = 0; i < ship1->getSize();i++){
              if(row == ship1->Pos[i].y && col == ship1->Pos[i].x){
                ship1->Pos[i].hitMarker = 1;
              }
            }

            for(int i = 0; i < ship2->getSize();i++){
              if(row == ship2->Pos[i].y && col == ship2->Pos[i].x){
                ship2->Pos[i].hitMarker = 1;
              }
            }

            for(int i = 0; i < ship3->getSize();i++){
              if(row == ship3->Pos[i].y && col == ship3->Pos[i].x){
                ship3->Pos[i].hitMarker = 1;
              }
            }
          }
        }
    }
    
  }
  // adds a position in the Pos array and updates the array size
//  Serial.println(col);
//  Serial.println(row);
  bool acheck = checkCoordinateInBoard(col, row, tempBoard);
//  Serial.println(acheck);
  //delay(10000); 
  if(!checkCoordinateInBoard(col, row, tempBoard)){
    Serial.println(F("looptydoopty"));
    Position tempPos;
    tempPos.x = col;
    tempPos.y = row;
    tempPos.hitMarker = 2;
    tempBoard->setMissPos(tempPos);
  }
  
  return value;
}

