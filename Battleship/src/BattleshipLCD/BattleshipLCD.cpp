/* Display messages on the LCD display.
   Written by SamridKC
   Converted to .h & .cpp file by Kevin.

	Basically copy-pasted from BattleshipLCD.ino
	but the .h & .cpp lets the main sketch code use this.
 */
/*
#include "Arduino.h" // For Arduino functions like delay()
#include "BattleshipLCD.h"
#include "../PresentationAbstraction/GameEvent.h"



void setup()   /*----( SETUP: RUNS ONCE )----*/
//{
  
//}/*--(end setup )---*/
/*
void eventLCD(const GameEvent input, const Position pos) {

  switch (input){
    case hit:
      hit_();
      break;
    case miss:
      missed();
      break;
    case sink:
      sunk();
      break;
     case player_Loss:
      endOfGame(pos.x); // Assuming Player 1 won
      delay(3000);
      highScore(20);  // assuming high score(lowest number of turns needed to win game was 20)
  }
}

void instructUser() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Enter position"));
  lcd.setCursor(0,1);
  lcd.print(F("to shoot (x,y)"));
}

/*void hit_() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("You hit "));
}

void missed() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Sorry! "));
  lcd.setCursor(0,1);
  lcd.print(F("You missed "));
}

void sunk() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Congratulations! "));
  lcd.setCursor(0,1);
  lcd.print(F("Ship sunk "));
}

void endOfGame(int x) {
  lcd.clear();
  int playerNo = x;
  lcd.setCursor(0,0);
  lcd.print(F("Player: "));
  lcd.setCursor(8,0);
  lcd.print(playerNo);
  lcd.setCursor(0,1);
  lcd.print(F("You win"));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Victory!"));
}
void highScore(int highSc) {
  lcd.clear();
  int x = highSc;
  lcd.setCursor(0,0);
  lcd.print(F("High Score: "));
  lcd.setCursor(0,1);
  lcd.print(x);
}
/* ( THE END )

}*/
