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

LedControl lc = LedControl(12,11,10,2);
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
  Serial.begin(9600);
  for(int index=0;index<lc.getDeviceCount();index++) {
        lc.shutdown(index,false); 
        lc.setIntensity(index,ledBrightness);
        lc.clearDisplay(index);
    }


//
  Position p0;
  p0.x = 2;
  p0.y = 3;
  p0.hitMarker = 1;

  Position p1;
  p1.x = 4;
  p1.y = 5;
  p1.hitMarker = 1;

  Position p2;
  p2.x = 5;
  p2.y = 5;
  p2.hitMarker = 1;

  player1.setPos(p0);
  player1.setPos(p1);
  player1.setPos(p2);
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
//Serial.println(player1.getNumberOfPos());
//  lc.setLed(0,player1.getXPos(0),player1.getYPos(0), true);
  player1.display(lc);
  // display the attackBoard
//  displayLed(attackBoard);
}
