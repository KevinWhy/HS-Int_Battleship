/* Physical Keypad
 *		By Kevin Yang
 *
 * This class wraps the Keypad class,
 * and let it work as an AbstractKeypad.
 */

#include <Keypad.h>
#include "KeypadInterface.h"
#include "PhysicalKeypad.h"

// Define the Keymap.
// Only eleven keys might be used, so rest are set to '\0'
// Also, we don't need the chars for the numbers...
//     So, the number keys will be treated as bytes (key-10) = number
const char keys[KPD_ROWS][KPD_COLS] = {
  { 11,  12,  13,'\0'},
  { 14,  15,  16,'\0'},
  { 17,  18,'\0','\0'},
  {'C','\0', 'E','\0'}
};

PhysicalKeypad::PhysicalKeypad(const byte rowPins[KPD_ROWS], const byte colPins[KPD_COLS])
  : kpd(makeKeymap(keys), rowPins, colPins, KPD_ROWS, KPD_COLS) { } // Done this way because Keypad needs to be defined right when this object is created

char PhysicalKeypad::getKey() {
	return kpd.getKey();
}
