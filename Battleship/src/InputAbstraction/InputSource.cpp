
#include "Arduino.h" // To DEBUG
#include "InputSource.h"

/****************************/

/* Returns true if x, y is on the board
 */
bool InputSource::isPosValid(const int newXPos, const int newYPos) {
  return (newXPos >= 1 && newXPos <= 8
       && newYPos >= 1 && newYPos <= 8);
}

/* These functions are called to change the currPos.
 */
void InputSource::setX(const int newXPos) {
  changingPos.x = newXPos;
  inputChanged(changingPos);
}
void InputSource::setY(const int newYPos) {
  changingPos.y = newYPos;
  inputChanged(changingPos);
}
void InputSource::setPos(const int newXPos, const int newYPos) { // This only calls inputChanged() once
  changingPos.x = newXPos;
  changingPos.y = newYPos;
  inputChanged(changingPos);
}
/* When user decides to send the input, let program read it.
 */
void InputSource::finalizePos() {
  nextPos = {changingPos.x, changingPos.y};
  hasNextPos = true;
}

/* When subclass tells InputSource that input has changed...
 * Invoke onChangeFunc()
 */
void InputSource::inputChanged(const Position currPos) {
  if (onChangeFunc != NULL) {
    onChangeFunc(currPos);
  }
}

/****************************/

InputSource::InputSource() {
  changingPos = {0,0};
  nextPos = INVALID_POS;
  hasNextPos = false;
  onChangeFunc = NULL;
}

/****************************/

/* Returns true if the InputSource has a nextPos ready.
 */
bool InputSource::hasInput() {
  return hasNextPos;
}
/* Returns nextPos.
 * If there hasn't been a nextPos, returns INVALID_POS.
 */
Position InputSource::getNextPos() {
  if (!hasNextPos)
    return INVALID_POS;
  // Return input, and say it can't be read anymore
  hasNextPos = false;
    return nextPos;
}


/* Keep track of which function to call when the input changes.
 */
void InputSource::onInputChange(void (*onChangeFunc)(Position currPos)) {
  if (this->onChangeFunc != NULL && this->onChangeFunc != onChangeFunc)
    Serial.println(F("WARNING: Replaced function listening to 'onInputChange'!"));
  this->onChangeFunc = onChangeFunc;
}
