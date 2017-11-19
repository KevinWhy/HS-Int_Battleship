#ifndef BOARD_ABSTRACT_H
#define BOARD_ABSTRACT_H

// This will store the coordinates that are in use and the type of hitMarker they are.
// They are initialized to -1

struct Position{
  int x;
  int y;
  int hitMarker; // 0 for not shot, 1 for hit, 2 for miss
};

const int MAX_POS = 64; //MAX number of positional coordinates on display board

class Board{
  private:
    Position Pos[MAX_POS];
    int displayNumber = 0;
    int numberOfPos = 0;
    
  public:
    board(); // initialize all board states to all false 
    
    int getXPos(int posIndex);
    int getYPos(int posIndex);
    int getHMarker(int posIndex);
    int getDisplayNumber(){return displayNumber;};
    int getNumberOfPos(){return numberOfPos;};

    //void setPos()
    
};
#endif

