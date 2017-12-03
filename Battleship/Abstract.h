#ifndef BATTLESHIP_ABSTRACT_H
#define BATTLESHIP_ABSTRACT_H

#include "Board.h"

int const shipMaxSize = 5;
struct Ship {

    Position Pos[shipMaxSize];
    bool state; // sunken or not true = float; false = sunken
    int shipSize; // size of ship
    
    Ship();
    Ship(bool shipSt, int shipSi);
    void setPos(int index, int xPos, int yPos, short hitMark);
    Position* getPos();
    int getSize();
    bool getShipState();

    bool checkShipSunkandUpdateState();
};

void shipInit(Ship *ship, Position posArr[]);

#endif
