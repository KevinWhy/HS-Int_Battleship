/* Battleship using arduinos and 8x8 led matrix MAX7219

   Has a demo of:
   - Input Abstraction
       You can use SerialInput (default) or KeypadInput.
   - Presentation Abstraction (aka: GameEvent listeners)
       Two functions respond to game "Ticks" & inputs.
*/

#include "Abstract.h"
#include "ship_placement.cpp"
#include "/Users/riteshsood/Documents/GitHub/HS-Int_Battleship/Led/Board.h"
#include "src/PresentationAbstraction/GameEvent.h"

#include "src/InputAbstraction/SerialInputSource.h"
#include "src/InputAbstraction/KeypadInputSource.h"
// To use KeypadInputSource, need to specify where it uses a Keypad or an Arduino
#include "src/InputAbstraction/KeypadInterface/PhysicalKeypad.h"
#include "src/InputAbstraction/KeypadInterface/ArduinoKeypad.h"
#include "LedControl.h" //  need the library
#include <Keypad.h>
LedControl lc=LedControl(16,15,14,1); //
// bool values to step move forward with the program once the ships are placed
bool p1_placed = false;
bool p2_placed = false;

// the display boards
Board ship_board1(0);
Board ship_board2(2);
/********************************/
//ship objects
Ship carrier(true, 5);
  Ship battleship(true, 4);
  Ship cruiser(true, 3);

  Ship carrier_2(true, 5);
  Ship battleship_2(true, 4);
  Ship cruiser_2(true, 3);
// Define keypad for KeypadInputSource
const byte rowPins[KPD_ROWS] = {8, 7, 6, 5};
const byte colPins[KPD_COLS] = {12, 11, 10, 9};
PhysicalKeypad keypd1(rowPins, colPins);
// Use Arduino for KeypadInputSource
const byte arduino_rxPin = 4;
const byte arduino_txPin = 5;
//ArduinoKeypad keypd(arduino_rxPin, arduino_txPin);
// Use some keypad as InputSource
//InputSource* player2 = new KeypadInputSource(&keypd);
InputSource* player1 = new KeypadInputSource(&keypd1);

// Use SerialInput
//InputSource* playerIn = new SerialInputSource();

/* This function is called when the player is planning to send a different input.
   However, they may change it a few more times before actually sending input.
   Should be used for presenting input as it changes (on LCD display)?
*/
void onKeypadChange(Position currPos) {
  // For now, just print the position the player is considering
  Serial.print("\t\tmaybe... (");
  Serial.print(currPos.x);
  Serial.print(",");
  Serial.print(currPos.y);
  Serial.println(")");
}

/********************************/

void setup() {
  // Example: Create some ships
  

  //Position posArray[shipMaxSize]; // store coordinates in posArray to be set by shipInit
  //shipInit(&carrier, posArray);

  // Input Abstraction demo...
  Serial.begin(9600);
  //player2->onInputChange(onKeypadChange); // Bind function to when input changes
  player1->onInputChange(onKeypadChange);

  // Have two functions listen for the DEBUG GameEvents
  listenForGameEvents(onGameEventPrint);
  listenForGameEvents(dullListener);
}

unsigned long ev_msCount = millis(); // Used for example GameEvent: EV_Ticker
void loop() {
  //player2->loop();
  player1->loop();

  // When input has been read...

  //display welcome screen


  while (p1_placed == false || p2_placed == false)
  {
    shipInit(&carrier, shipPlacement(5, ship_board1, player1, lc));
    shipInit(&battleship, shipPlacement(4, ship_board1, player1, lc));
    shipInit(&cruiser, shipPlacement(3, ship_board1, player1, lc));

    //shipInit(&carrier_2, shipPlacement(5, ship_board2));
    //shipInit(&battleship_2, shipPlacement(4, ship_board2));
    //shipInit(&cruiser_2, shipPlacement(3, ship_board2));

    int check1 = ship_board1.getNumberOfPos();
    int check2 = ship_board2.getNumberOfPos();

    if (check1 == 12 && check2 == 12)
    {
      p1_placed == true;
      p2_placed == true;
    }
  }





  // Every 3 seconds, fire EV_Ticker (Example GameEvent)
  if (millis() - ev_msCount > 3000) {
    fireGameEvent(EV_Ticker, INVALID_POS);
    ev_msCount = millis();
  }
}
