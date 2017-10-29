/* Keypad Input Source
 *    By Kevin Yang
 * 
 * This class allows a user to send input via a keypad.
 * Type in two numbers, and press Enter to send it.
 */

#include "Arduino.h" // To DEBUG
#include "KeypadInputSource.h"

// Define the Keymap.
// Only eleven keys might be used, so rest are set to '\0'
// Also, we don't need the chars for the numbers...
//     So, the number keys will be treated as bytes (key-10) = number
const char keys[KPD_ROWS][KPD_COLS] = {
  { 11, 12, 13,'\0'},
  { 14, 15, 16,'\0'},
  { 17, 18, 19,'\0'},
  {'C', 10,'E','\0'}
};

#define KPIN_CHANGE_X 0
#define KPIN_CHANGE_Y 1
#define KPIN_CHANGE_NONE 2

void KeypadInputSource::resetChangingPos() {
  changingPos = {0,0};
  changeState = KPIN_CHANGE_X; // Let user type input again
  inputChanged(changingPos); // Notify code that input changed
}

KeypadInputSource::KeypadInputSource(const byte rowPins[], const byte colPins[])
  : kpd(makeKeymap(keys), rowPins, colPins, KPD_ROWS, KPD_COLS) { // Done this way because Keypad needs to be defined right when this object is created
  hasNextPos = false;
  changingPos = {0,0};
  changeState = KPIN_CHANGE_X;
  resetChangingPos();
}

bool KeypadInputSource::hasInput() {
  return hasNextPos;
}

Position KeypadInputSource::getNextPos() {
  if (!hasNextPos)
	return INVALID_POS;
  hasNextPos = false; // Once input is read, don't return that position anymore
  resetChangingPos(); // Reset input
  return nextPos;
}

/* This class needs to poll for input.
*/
void KeypadInputSource::loop() {
  char key = kpd.getKey();
  switch(key) {
  case 'E': // Pressed Enter
	changeState = KPIN_CHANGE_NONE; // Don't let user change input anymore
	// Allow code to read input now
	nextPos = changingPos;
	hasNextPos = true;
	break;
  case 'C': // Pressed Clear
	if (changeState != KPIN_CHANGE_NONE) // If changing a number, restart input
	  resetChangingPos();
	break;
  case '\0': // No key (or invalid key) entered
	break;
  default: // Number key was pushed
	byte num = int(key) -10;
	
	// After a number is input, wait for next number
	if (changeState == KPIN_CHANGE_X) {
	  changingPos.x = num;
	  changeState = KPIN_CHANGE_Y;
	  inputChanged(changingPos); // Notify code that input changed
	  
	} else if (changeState == KPIN_CHANGE_Y) {
	  changingPos.y = num;
	  changeState = KPIN_CHANGE_X; // & Let user change the x-position
	  inputChanged(changingPos); // Notify code that input changed
	}
  }
}
