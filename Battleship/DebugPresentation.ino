
#include "src/PresentationAbstraction/GameEvent.h"

/* Both of these functions are called when a GameEvent occurs.
 *  There's a generic DEBUG printer for the events,
 *  and a "LazyGuy" that only cares for Ev_Ticker.
 */

void onGameEventPrint(const GameEvent ev, const Position pos) {
  Serial.print("\tGAME EVENT: ");
  switch (ev) {
  case EV_Input:
    Serial.print("Input read...");
  break;
  case EV_Ticker:
    Serial.print("Tick tick");
  break;
  }
  Serial.print(" at (");
  Serial.print(pos.x);
  Serial.print(",");
  Serial.print(pos.y);
  Serial.println(")");
}

/* This listener only cares for Ticker events. */
void dullListener(const GameEvent ev, const Position pos) {
  switch (ev) {
  case EV_Input:
    Serial.println("\t\tDull guy: Input? Meh.");
  break;
  case EV_Ticker:
    Serial.println("\t\tDull guy: Tickers? Oh yes please!");
  break;
  }
}

