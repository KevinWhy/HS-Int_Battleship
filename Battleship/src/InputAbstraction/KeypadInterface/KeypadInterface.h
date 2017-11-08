/* Keypad Interface
 *		By Kevin Yang
 *
 * This class acts as an interface to a Keypad.
 * It is done this way to allow the
 * second Arduino to mimic a keypad on SoftwareSerial.
 */

#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H

class KeypadInterface {
public:
	virtual char getKey() = 0;
};

#endif
