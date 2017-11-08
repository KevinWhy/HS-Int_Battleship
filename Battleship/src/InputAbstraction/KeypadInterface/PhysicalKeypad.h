/* Physical Keypad
 *		By Kevin Yang
 *
 * This class wraps the Keypad class,
 * and let it work as an AbstractKeypad.
 */

#ifndef PHYSICAL_KEYPAD_H
#define PHYSICAL_KEYPAD_H

#include <Keypad.h>
#include "KeypadInterface.h"

const byte KPD_ROWS = 4; // Four rows
const byte KPD_COLS = 4; // Four columns

class PhysicalKeypad : public KeypadInterface {
private:
	Keypad kpd;
public:
	PhysicalKeypad(const byte rowPins[KPD_ROWS], const byte colPins[KPD_COLS]);
	virtual char getKey();
};

#endif
