// LedControl.h required for MAX72XX
#include "LedControl.h"
#include "Board.h"

/* Create a new LedControl variable.
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 12 is connected to the DATA IN-pin of the first MAX7221
 * Pin 11 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221
 * The last argument is the number of MAX7XX devices, can be linked daisy chain
 * There will only be a single MAX7221 attached to the arduino 
 */ 

//const int MAX_BOARDSIZE = 8;
LedControl lc = LedControl(12,11,10,1);
int ledBrightness = 8;

int interval = 1000;

Board attackBoard;
Board defendBoard;

void setup() {
  for(int index=0;index<lc.getDeviceCount();index++) {
        lc.shutdown(index,false); 
        lc.setIntensity(index,ledBrightness);
        lc.clearDisplay(index);
    }
}

void displayLed(Board board){
  int i = 0;
  while(i < board.getNumberOfPos()){
    if(board.getHMarker(i) == 0){
      lc.setLed(board.getDisplayNumber(), board.getXPos(i), board.getYPos(i), false);
      
    }else if(board.getHMarker(i) == 1){
      
      lc.setLed(board.getDisplayNumber(), board.getXPos(i), board.getYPos(i), true);
      lc.setLed(board.getDisplayNumber(), board.getXPos(i), board.getYPos(i), false);
      
      
    }else if(board.getHMarker(i) == 2){
      lc.setLed(board.getDisplayNumber(), board.getXPos(i), board.getYPos(i), true);
    } 
    i++;
  }
}
  
void loop() {
  // display the attackBoard
  displayLed(attackBoard);
  
  // display the defendBoard
}
