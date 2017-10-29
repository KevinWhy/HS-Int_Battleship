
#include "Arduino.h" // To DEBUG
#include "InputSource.h"

/* When subclass tells InputSource that input has changed...
 * Invoke onChangeFunc()
 */
void InputSource::inputChanged(const Position currPos) {
  if (onChangeFunc != NULL) {
    onChangeFunc(currPos);
  }
}

/* Keep track of which function to call when the input changes.
 */
void InputSource::onInputChange(void (*onChangeFunc)(Position currPos)) {
  if (this->onChangeFunc != NULL && this->onChangeFunc != onChangeFunc)
    Serial.println("WARNING: Replaced function listening to 'onInputChange'!");
  this->onChangeFunc = onChangeFunc;
}
