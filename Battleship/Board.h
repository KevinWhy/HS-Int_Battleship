#include "LedControl.h"

#ifndef BOARD_ABSTRACT_H
#define BOARD_ABSTRACT_H

// This will store the coordinates that are in use and the type of hitMarker they are.
// They are initialized to -1

struct Position{
  char x;
  char y;
  short hitMarker; // 0 for not shot, 1 for hit, 2 for miss
  //bool ledState; // used for millis blinking  NOT TO BE CHANGED outside Board
};

const int MAX_POS = 64; //MAX number of positional coordinates on display board

struct Board{
  
    Position Pos[MAX_POS]; // Array to hold all the position/coordinates in use
    int boardNumber = 0; // Display number, used with the Ledcontrol.h library
    int numberOfPos = 0; // Stores the number of position in our array of position/coordinates

    bool ledS = false;
    
    Board(int boardN); // initialize all board states to all false
    void printa();
    // get functions for our Position struct, pass in index of array and returns the corresponding data
    int getXPos(int posIndex);
    int getYPos(int posIndex);
    int getHMarker(int posIndex);
    bool getLedState(int posIndex);

    // get functions for board data
    int getboardNumber(){return boardNumber;};
    int getNumberOfPos(){return numberOfPos;};

    // set functions for Position array
    void setLedState(int posIndex, bool state);
    void setPos(Position passedInPos);
    void setMissPos(Position passedInPos);

    // display function for board
    void display(LedControl lc);

};
#endif

