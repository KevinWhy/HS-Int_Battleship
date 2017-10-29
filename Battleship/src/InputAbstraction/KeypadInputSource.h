/* Keypad Input Source
 *    By Kevin Yang
 * 
 * This class allows a user to send input via a keypad.
 * Type in two numbers, and press Enter to send it.
 */
#ifndef KEYPAD_INPUT_SOURCE_H
#define KEYPAD_INPUT_SOURCE_H

#include <Keypad.h>
#include "InputSource.h"

const byte KPD_ROWS = 4; // Four rows
const byte KPD_COLS = 4; // Four columns

class KeypadInputSource : public InputSource {
  private:
    Keypad kpd;
    Position nextPos;
    bool hasNextPos;
    Position changingPos;
    byte changeState;
    
    void resetChangingPos();
    
  public:
    KeypadInputSource(const byte rowPins[KPD_ROWS], const byte colPins[KPD_COLS]);
    
    virtual bool hasInput();
    virtual Position getNextPos();
    
    /* This class needs to poll for input.
    */
    virtual void loop();
};

#endif
