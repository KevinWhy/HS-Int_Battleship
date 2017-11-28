/* Serial Input Source
 *    By Kevin Yang
 * 
 * This class allows a user to send input via Serial.
 * This is a test class for SerialInput.
 * 
 * Need to call Serial.begin() in the main file's setup()
 * 
 * Assumes that the user ALWAYS types in two numbers,
 * separated by a space.
 */

#include "Arduino.h" // Allow cpp file to use Arduino functions
#include "SerialInputSource.h"

int SerialInputSource::readInt() {
  bool intRead = false;
  int inNum = 0;
  
  delay(10); // Give enough time for the rest of the input to be sent
  // Read input until done
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (isDigit(inChar)) {
      intRead = true;
      inNum = inNum*10 +(inChar -'0');
    } else if (intRead) { // char != number && number already found...
      return inNum;
    }
  }
  
  if (!intRead)
    return -1;
  return inNum;
}

/* This class doesn't need to loop. */
void SerialInputSource::loop() {
  if (Serial.available() > 0) {
    int xPos = readInt();
    int yPos = readInt();
    if (isPosValid(xPos, yPos)) {
      setPos(xPos, yPos);
      finalizePos();
    }
  }
}
