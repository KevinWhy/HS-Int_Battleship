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

/********************************/

// Use SerialInput
InputSource* playerIn = new SerialInputSource();
// Use keypad input
//    const byte rowPins[KPD_ROWS] = {5, 6, 7, 8};
//    const byte colPins[KPD_COLS] = {9, 10, 11, 12}; 
//InputSource* playerIn = new KeypadInputSource(rowPins, colPins);

void onKeypadChange(Position currPos) {
  Serial.print("\t\tmaybe... (");
  Serial.print(currPos.x);
  Serial.print(",");
  Serial.print(currPos.y);
  Serial.println(")");
}

/********************************/

void setup() {
  Ship carrier(true,5);
  Ship battleship(true,4);
  Ship cruiser(true,3);
  Ship submarine(true,3);
  Ship destroyer(true,2);

  Position posArray[shipMaxSize]; // store coordinates in posArray to be set by shipInit
  shipInit(&carrier, posArray);
  
  Serial.begin(9600);
  playerIn->onInputChange(onKeypadChange); // Bind function to when input changes

  // Have two functions listen for the DEBUG GameEvents
  listenForGameEvents(onGameEventPrint);
  listenForGameEvents(dullListener);
}

unsigned long ev_msCount = millis(); // Used for example GameEvent, EV_Ticker
void loop() {
  playerIn->loop();
  
  if (playerIn->hasInput()) {
    Position pos = playerIn->getNextPos();
    Serial.print("Arduino recieved input. Pos: (");
    Serial.print(pos.x);
    Serial.print(", ");
    Serial.print(pos.y);
    Serial.println(")");
    delay(1000);
    fireGameEvent(EV_Input, pos); // Fire an example GameEvent
  }
  
  // Every 3 seconds, fire EV_Ticker (Example GameEvent)
  if (millis() - ev_msCount > 3000) {
    fireGameEvent(EV_Ticker, INVALID_POS);
    ev_msCount = millis();
  }
}
