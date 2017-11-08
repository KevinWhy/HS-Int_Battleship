/* Battleship using arduinos and 8x8 led matrix MAX7219
 * 
 * Has a demo of:
 * - Input Abstraction
 *     You can use SerialInput (default) or KeypadInput.
 * - Presentation Abstraction (aka: GameEvent listeners)
 *     Two functions respond to game "Ticks" & inputs.
 */

#include "Abstract.h"
#include "src/PresentationAbstraction/GameEvent.h"

#include "src/InputAbstraction/SerialInputSource.h"
#include "src/InputAbstraction/KeypadInputSource.h"
// To use KeypadInputSource, need to specify where it uses a Keypad or an Arduino
#include "src/InputAbstraction/KeypadInterface/PhysicalKeypad.h"
#include "src/InputAbstraction/KeypadInterface/ArduinoKeypad.h"

/********************************/

// Define keypad for KeypadInputSource
//    const byte rowPins[KPD_ROWS] = {5, 6, 7, 8};
//    const byte colPins[KPD_COLS] = {9, 10, 11, 12}; 
//PhysicalKeypad keypd(rowPins, colPins);
// Use Arduino for KeypadInputSource
    const byte arduino_rxPin = 4;
    const byte arduino_txPin = 5;
ArduinoKeypad keypd(arduino_rxPin, arduino_txPin);
// Use some keypad as InputSource
InputSource* playerIn = new KeypadInputSource(&keypd);

// Use SerialInput
//InputSource* playerIn = new SerialInputSource();

/* This function is called when the player is planning to send a different input.
 * However, they may change it a few more times before actually sending input.
 * Should be used for presenting input as it changes (on LCD display)?
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
  Ship carrier(true,5);
  Ship battleship(true,4);
  Ship cruiser(true,3);
  Ship submarine(true,3);
  Ship destroyer(true,2);

  Position posArray[shipMaxSize]; // store coordinates in posArray to be set by shipInit
  shipInit(&carrier, posArray);
  
  // Input Abstraction demo...
  Serial.begin(9600);
  playerIn->onInputChange(onKeypadChange); // Bind function to when input changes

  // Have two functions listen for the DEBUG GameEvents
  listenForGameEvents(onGameEventPrint);
  listenForGameEvents(dullListener);
}

unsigned long ev_msCount = millis(); // Used for example GameEvent: EV_Ticker
void loop() {
  playerIn->loop();
  
  // When input has been read...
  if (playerIn->hasInput()) {
    Position pos = playerIn->getNextPos();
    // Display the position
    Serial.print("Arduino recieved input. Pos: (");
    Serial.print(pos.x);
    Serial.print(", ");
    Serial.print(pos.y);
    Serial.println(")");
    
    // Fire an example GameEvent, one second later
    delay(1000);
    fireGameEvent(EV_Input, pos);
  }
  
  // Every 3 seconds, fire EV_Ticker (Example GameEvent)
  if (millis() - ev_msCount > 3000) {
    fireGameEvent(EV_Ticker, INVALID_POS);
    ev_msCount = millis();
  }
}
