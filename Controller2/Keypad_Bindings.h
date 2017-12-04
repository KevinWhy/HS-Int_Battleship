/* Defines stuff for the Keypad.
 * Should use the same key array as the main Battleship sketch.
 */
#ifndef CONTROLLER2_KEYPAD_H
#define CONTROLLER2_KEYPAD_H

const byte KPD_ROWS = 4; // Four rows
const byte KPD_COLS = 4; // Four columns

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

  #ifdef PRO_MINI
      const byte rowPins[KPD_ROWS] = {5, 6, 7, 8};
      const byte colPins[KPD_COLS] = {9, 10, 11, 12}; 
  #elif defined(UNO)
      const byte rowPins[KPD_ROWS] = {8, 7, 6, 5};
      const byte colPins[KPD_COLS] = {12, 11, 10, 9}; 
  #endif

#endif

