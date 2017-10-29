/* Project: Abstractions
 *    designed by Kevin Yang
 * 
 * These abstractions will be used to separate game logic
 * from input & display handling.
 */

#include "src/InputAbstraction/SerialInputSource.h"
#include "src/InputAbstraction/KeypadInputSource.h"

/********************************/

//InputSource* playerIn = new SerialInputSource();

    const byte rowPins[KPD_ROWS] = {5, 6, 7, 8};
    const byte colPins[KPD_COLS] = {9, 10, 11, 12}; 
InputSource* playerIn = new KeypadInputSource(rowPins, colPins);

/********************************/

void onKeypadChange(Position currPos) {
  Serial.print("\t\tmaybe... (");
  Serial.print(currPos.x);
  Serial.print(",");
  Serial.print(currPos.y);
  Serial.println(")");
}

/********************************/

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
  playerIn->onInputChange(onKeypadChange); // Bind function to when input changes
}

void loop() {
  playerIn->loop();
  
  if (playerIn->hasInput() && Serial.available() > 0) {
    while (Serial.available() > 0)    Serial.read(); // DEBUG: Also wait for Serial input before reading
    
    Position pos = playerIn->getNextPos();
    Serial.print("\tPos: (");
    Serial.print(pos.x);
    Serial.print(", ");
    Serial.print(pos.y);
    Serial.println(")");
    delay(250);
  }
}

