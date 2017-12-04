/* The second controller just reads values from a keypad...
 *  and sends it to the main Arduino.
 * 
 * I use SoftwareSerial so that Serial can be used by SerialMonitor.
 */

#define UNO // To determine pin layouts

#include <SoftwareSerial.h>
#ifdef PRO_MINI
const byte RX_PIN = 4;
const byte TX_PIN = 5;
#elif defined(UNO)
const byte RX_PIN = 3;
const byte TX_PIN = 4;
#endif
SoftwareSerial softSerial(RX_PIN, TX_PIN);

// Use keypad input
#include <Keypad.h>
#include "Keypad_Bindings.h" // Header file defines all the pins used by Keypad

Keypad kpd(makeKeymap(keys), rowPins, colPins, KPD_ROWS, KPD_COLS);

/****************************/

void setup() {
  softSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  char key = kpd.getKey();
  if (key != '\0') { // If key has been sent...
    softSerial.write(key);
    if (key < 20)
      Serial.println(key -10); // Subtracting char by int returns an int... So print the int value sent!
    else // key is an actual character
      Serial.println(key);
  }
}
