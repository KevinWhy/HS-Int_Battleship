

#include <EEPROM.h>

void setup() {
   Serial.begin(9600);
   Serial.print(setHighScore(25));
   
}

void loop() {
// Empty loop 
}

int setHighScore(int score){
  const int flagAddress = 0;    // first time power up flag
  const int noHignScoreSetYet = 128;   // value to indicate that the it is the first time being powered up
  const int scoreAddress = 1;
  int highScore = 100;
  int test;
   int value = EEPROM.read(flagAddress);      // read the first time power up value
   highScore = EEPROM.read(scoreAddress);
  
   if (value != 128) {                      // if value is not 128 then assume that first power up
    Serial.println("No high score has been set yet.");
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
  Serial.print("High Score: ");
  Serial.println(test);
  return highScore;
}

