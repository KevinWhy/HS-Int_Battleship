/* Serial Input Source
 *    By Kevin Yang
 * 
 * This class allows a user to send input via Serial.
 * This is a test class for SerialInput.
 * 
 * Assumes that the user ALWAYS types in two numbers,
 * seperated by a space.
 * 
 * Bug: User cannot input position 0.
 */
#ifndef SERIAL_INPUT_SOURCE_H
#define SERIAL_INPUT_SOURCE_H
#include "InputSource.h"

class SerialInputSource : public InputSource {
  private:
    Position pos;
    bool hasPos = false;

    /* Gets an int from the input.
     */
    int readInt() {
      
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
      int xPos = 0, yPos = 0;
      bool xFound = false, yFound = false;
      while (Serial.available() > 0) {
        char inChar = Serial.read();

        if (!xFound) { // Find x
          if (isDigit(inChar))
            xPos = xPos*10 +(inChar -'0');
          else if (xPos != 0)
            xFound = true;
        } else { // Find y
          if (isDigit(inChar)) {
            yPos = yPos*10 +(inChar -'0');
            yFound = true;
          } else if (yPos != 0) {
            break;
          }
        }
      }

      if (yFound)
        return {xPos, yPos};
      return INVALID_POS;
    }
};

#endif

