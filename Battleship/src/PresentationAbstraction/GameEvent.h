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
 * 
 * Assumes that less than 10 functions will listen for events.
 * 
 * Enum Reference: https://msdn.microsoft.com/en-us/library/2dzy4k6e.aspx
 */

#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include "../../Abstract.h" // For the Position struct

enum GameEvent {
  EV_Input, EV_Ticker, hit, miss, sink, player_Loss // Example events
};

/***********************************/

/* When a GameEvent occurs, call eventFunc.
 */
void listenForGameEvents(void (*eventFunc)(const GameEvent ev, const Position pos));

/* Call this function to say that a GameEvent occured.
 */
void fireGameEvent(const GameEvent ev, const Position pos);

#endif
