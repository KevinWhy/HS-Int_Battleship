/* Project: Abstractions
 *    designed by Kevin Yang
 * 
 * These abstractions will be used to separate game logic
 * from input & display handling.
 */

struct Position{ // Should be defined in a header file
  int x;
  int y;
};
#include "SerialInputSource.h"

InputSource* playerIn = new SerialInputSource();
void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {
  if (playerIn->hasInput()) {
    Position pos = playerIn->getNextPos();
    Serial.print("\tPos: (");
    Serial.print(pos.x);
    Serial.print(", ");
    Serial.print(pos.y);
    Serial.println(")");
  }
  delay(250);
//  Serial.print("?");
}

