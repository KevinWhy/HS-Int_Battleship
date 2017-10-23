/* Battleship using arduinos and 8x8 led matrix MAX7219 */

int const shipMaxSize = 5;

#include "Abstract.h"

void setup() {
  Ship carrier(true,5);
  Ship battleship(true,4);
  Ship cruiser(true,3);
  Ship submarine(true,3);
  Ship destroyer(true,2);

  Position posArray[shipMaxSize]; // store coordinates in posArray to be set by shipInit
  shipInit(&carrier, posArray);
}

void loop() {
  // put your main code here, to run repeatedly:
}
