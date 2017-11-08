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
#include "KeypadInterface/KeypadInterface.h"

class KeypadInputSource : public InputSource {
  private:
    KeypadInterface const* kpd;
    byte changeState;
    
    void resetChangingPos();
    
  public:
    KeypadInputSource(KeypadInterface const* kpd);
    virtual Position getNextPos();
    
    /* This class needs to poll for input.
    */
    virtual void loop();
};

#endif
