/* Game Event
 *    By Kevin Yang
 * 
 * This abstraction seperates game logic from its presentation.
 * Idea: (Publish / Subscribe pattern)
 *   1. Events are defined as members of the DisplayEvent enum.
 *   2. When an event happens, game logic will call a function, and say that:
 *          "An event has occured!"
 *   3. This abstraction will call a function from all the listeners.
 *   4. The functions / listeners will respond to the event.
 *
 * Array of function pointers Reference: http://www.java2s.com/Code/C/Function/Arrayoffunctionpointer.htm
 */

#define MAX_LISTENERS 10 // If more than 10 functions try to listen for events, this program will crash!

#include "Arduino.h" // To DEBUG
#include "GameEvent.h"

void (*eventFuncs[MAX_LISTENERS])(const GameEvent ev, const Position pos) = {};
int numListeners = 0;

/* When a GameEvent occurs, call eventFunc.
 */
void listenForGameEvents(void (*eventFunc)(const GameEvent ev, const Position pos)) {
  if (numListeners >= MAX_LISTENERS) {
    Serial.println(F("ERROR: Tried to add too many listeners!"));
  }
  eventFuncs[numListeners++] = eventFunc;
}

/* Call this function to say that a GameEvent occured.
 */
void fireGameEvent(const GameEvent ev, const Position pos) {
  for (int i = 0; i < numListeners; ++i)
    eventFuncs[i](ev, pos);
}

