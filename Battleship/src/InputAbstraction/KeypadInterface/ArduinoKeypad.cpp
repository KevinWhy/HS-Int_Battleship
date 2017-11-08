/* Arduino Keypad
 *		By Kevin Yang
 *
 * This class communicates with another Arduino via SoftwareSerial.
 * That Arduino is expected to send chars when the keypad is pressed.
 */

#include <SoftwareSerial.h>
#include "KeypadInterface.h"
#include "ArduinoKeypad.h"

#define SOFT_SERIAL_BAUD_RATE 9600

ArduinoKeypad::ArduinoKeypad(const byte rxPin, const byte txPin)
	: softSerial(rxPin, txPin) { // Create softSerial object
	softSerial.begin(SOFT_SERIAL_BAUD_RATE);
}

char ArduinoKeypad::getKey() { // Keys are recieved via SoftwareSerial
	return (softSerial.available() > 0) ? softSerial.read() : '\0';
}
