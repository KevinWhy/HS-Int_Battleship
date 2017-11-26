#ifndef BATTLESHIP_ABSTRACT_H
#define BATTLESHIP_ABSTRACT_H

#include "Board.h"

int const shipMaxSize = 5;
class Ship {
  private:
    Position Pos[shipMaxSize];
    bool state; // sunken or not true = float; false = sunken
    int shipSize; // size of ship

  public:
    Ship();
    Ship(bool shipSt, int shipSi);
    void setPos(int index, int xPos, int yPos);
    Position getPos();
    int getSize();
};

void shipInit(Ship *ship, Position posArr[]);

#endif
