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

LedControl lc = LedControl(12,11,10,1);
int ledBrightness = 8;

// Variables for millis blinking
//unsigned int previousMillis = 0;
//int interval = 1000;
bool ledState = false;

// sample Board objects, replace with your own Board object
Board player1;
Board player2;

void setup() {
  // Led matrix inititalization
  for(int index=0;index<lc.getDeviceCount();index++) {
        lc.shutdown(index,false); 
        lc.setIntensity(index,ledBrightness);
        lc.clearDisplay(index);
    }
}

// displayLed function
/*
 * Parameters: Takes in a Board object and displays the leds in use
 * on that Board object.
 * 
 * Implementation: Uses a awhile loop to check the hitMarker state 
 * of all the LEDs in use \and display accordingly.
 * 0 for not shot (off), 1 for hit(blink), 2 for miss(on)
 * 
 * hit: blink, miss: solid, 
 */
//void displayLed(Board board){
//  int i = 0;
//  while(i < board.getNumberOfPos()){
//    if(board.getHMarker(i) == 0){
//      lc.setLed(board.getboardNumber(), board.getXPos(i), board.getYPos(i), false);
//      
//    }else if(board.getHMarker(i) == 1){
//      if(millis() - previousMillis > interval) {
//        ledState = !board.getLedState(i);
//        board.setLedState(i, ledState);
//        lc.setLed(board.getboardNumber(), board.getXPos(i), board.getYPos(i), ledState);
//        previousMillis = millis();
//      } 
//      
//    }else if(board.getHMarker(i) == 2){
//      lc.setLed(board.getboardNumber(), board.getXPos(i), board.getYPos(i), true);
//    } 
//    i++;
//  }
//}
  
void loop() {
 // attackBoard.
  player1.display(lc);
  // display the attackBoard
//  displayLed(attackBoard);
}
