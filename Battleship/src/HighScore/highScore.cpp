/* Save & read high scores.
   Written by Narayan Ramjali
   Converted to .h & .cpp file by Kevin.

	Basically copy-pasted from highScore.ino
	but the .h & .cpp lets the main sketch code use this.
 */

#include "Arduino.h" // For Arduino functions like delay()
#include <EEPROM.h>
#include "highScore.h"

namespace ShipSound {
int setHighScore(int score){
  const int flagAddress = 0;    // first time power up flag
  const int noHignScoreSetYet = 128;   // value to indicate that the it is the first time being powered up
  const int scoreAddress = 1;
  int highScore = 100;
  int test;
   int value = EEPROM.read(flagAddress);      // read the first time power up value
   highScore = EEPROM.read(scoreAddress);
  
   if (value != 128) {                      // if value is not 128 then assume that first power up
    Serial.println(F("No high score has been set yet."));
    EEPROM.write(flagAddress, noHignScoreSetYet);
    EEPROM.write(scoreAddress, score);
    highScore = score;
   }
   else if (value == 128){
      if(score < highScore){
      EEPROM.write(scoreAddress, score);
      highScore = score;
     }
   }
  test = EEPROM.read(scoreAddress);
  Serial.print(F("High Score: "));
  Serial.println(test);
  return highScore;
}

}
