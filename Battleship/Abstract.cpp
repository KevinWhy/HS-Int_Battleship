#include "Abstract.h"

void Ship::setPos(int index, int xPos, int yPos, short hitMark){
  Pos[index].x = xPos;
  Pos[index].y = yPos;
  Pos[index].hitMarker = hitMark; 
}

Ship::Ship(){
}
Ship::Ship(bool shipSt, int shipSi){
  state = shipSt;
  shipSize = shipSi;
}

Position* Ship::getPos(){return Pos;}
int Ship::getSize(){return shipSize;}

void shipInit(Ship *ship, Position* posArr){
  for(int i = 0; i < ship->getSize(); i++){
    ship->setPos(i, posArr[i].x, posArr[i].y, 0);
  }
}

// return ship state
bool Ship::getShipState(){
  return state;
}

// checks all the positions of the ships, if all are hit then return TRUE for ship is sunk, FALSE for still alive
bool Ship::checkShipSunkandUpdateState(){
  
  bool Sink = true;
  if(state != false)
  {
    for(int i = 0; i < shipSize; i++){
    //Serial.println(Pos[i].hitMarker);
      if(Pos[i].hitMarker != 1){
         Sink = false;
         //break;
      }
    }
    this->state = !Sink;
  }
  else
    Sink = false;
    
  Serial.println(F("This is the ships state"));
  Serial.println(state);
  Serial.println(F("This is the sink state"));
  Serial.println(Sink);
  return Sink;
}

