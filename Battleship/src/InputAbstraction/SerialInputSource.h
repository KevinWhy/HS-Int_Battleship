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
    /* Gets an int from Serial.
     *    If Serial didn't have a number, returns -1.
     */
    int readInt();
    
  public:
    // Assumes that user sends two chars at once
    virtual void loop();
};

#endif

