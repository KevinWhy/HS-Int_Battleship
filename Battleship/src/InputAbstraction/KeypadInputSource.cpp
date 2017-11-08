/* Keypad Input Source
 *    By Kevin Yang
 * 
 * This class allows a user to send input via a keypad.
 * Type in two numbers, and press Enter to send it.
 * 
 * Calling base class function reference: https://stackoverflow.com/questions/672373/can-i-call-a-base-classs-virtual-function-if-im-overriding-it#672376
 */

#include "Arduino.h" // To DEBUG
#include "KeypadInputSource.h"

#define KPIN_CHANGE_X 0
#define KPIN_CHANGE_Y 1
#define KPIN_CHANGE_NONE 2

void KeypadInputSource::resetChangingPos() {
  setPos(0,0);
  changeState = KPIN_CHANGE_X; // Let user type input again
}

KeypadInputSource::KeypadInputSource(KeypadInterface const* kpd)
  : kpd(kpd) { // Done this way because Keypad needs to be defined right when this object is created
  changeState = KPIN_CHANGE_X;
}

Position KeypadInputSource::getNextPos() {
  resetChangingPos(); // Let user input stuff again
  return InputSource::getNextPos();
}

/* This class needs to poll for input.
*/
void KeypadInputSource::loop() {
  char key = kpd->getKey();
  switch(key) {
  case 'E': // Pressed Enter
	changeState = KPIN_CHANGE_NONE; // Don't let user change input anymore
	finalizePos(); // Allow code to read input now
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
	  changeState = KPIN_CHANGE_Y;
      setX(num);
	  
	} else if (changeState == KPIN_CHANGE_Y) {
	  changeState = KPIN_CHANGE_X; // Let user change the x-position
      setY(num);
	}
  }
}
