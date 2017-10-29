#include "Abstract.h"

void Ship::setPos(int index, int xPos, int yPos){
  Pos[index].x = xPos;
  Pos[index].y = yPos; 
}

Ship::Ship(){
}
Ship::Ship(bool shipSt, int shipSi){
  state = shipSt;
  shipSize = shipSi;
}

Position Ship::getPos(){return *Pos;}
int Ship::getSize(){return shipSize;}

void shipInit(Ship *ship, Position posArr[]){
  for(int i = 0; i < ship->getSize(); i++){
    ship->setPos(i, posArr[i].x, posArr[i].y);
  }
}

