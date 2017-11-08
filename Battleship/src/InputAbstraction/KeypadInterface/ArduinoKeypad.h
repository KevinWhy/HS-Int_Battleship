/* Arduino Keypad
 *		By Kevin Yang
 *
 * This class communicates with another Arduino via SoftwareSerial.
 * That Arduino is expected to send chars when the keypad is pressed.
 */

#ifndef ARDUINO_KEYPAD_H
#define ARDUINO_KEYPAD_H

#include "Arduino.h" // To use the byte type
#include <SoftwareSerial.h>
#include "KeypadInterface.h"

class ArduinoKeypad : public KeypadInterface {
private:
	SoftwareSerial softSerial;
public:
	ArduinoKeypad(const byte rxPin, const byte txPin);
	virtual char getKey();
};

#endif
