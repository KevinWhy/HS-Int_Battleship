/* Battleship using arduinos and 8x8 led matrix MAX7219 */

#include "Abstract.h"
#include "src/InputAbstraction/SerialInputSource.h"

/********************************/

InputSource* playerIn = new SerialInputSource();
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
}

void loop() {
  playerIn->loop();
  
  if (playerIn->hasInput()) {
    Position pos = playerIn->getNextPos();
    Serial.print("\tPos: (");
    Serial.print(pos.x);
    Serial.print(", ");
    Serial.print(pos.y);
    Serial.println(")");
    delay(250);
  }
}
