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
#ifndef SERIAL_INPUT_SOURCE_H
#define SERIAL_INPUT_SOURCE_H
#include "InputSource.h"

class SerialInputSource : public InputSource {
  private:
    Position pos;
    bool hasPos = false;

    /* Gets an int from Serial.
     *    If Serial didn't have a number, returns -1.
     */
    int readInt() {
      bool intRead = false;
      int inNum = 0;

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
    
  public:
    SerialInputSource() {
    }

    // Assumes that user sends two chars at once
    virtual bool hasInput() {
      return Serial.available() > 0;
    }
    
    virtual Position getNextPos() {
      // Read input until two numbers found
      int xPos = readInt();
      int yPos = readInt();
      if (xPos == -1 || yPos == -1)
        return INVALID_POS;
      
      return {xPos, yPos};
    }
};

#endif

