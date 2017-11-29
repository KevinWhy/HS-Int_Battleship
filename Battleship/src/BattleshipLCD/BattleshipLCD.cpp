/* Display messages on the LCD display.
   Written by SamridKC
   Converted to .h & .cpp file by Kevin.

	Basically copy-pasted from BattleshipLCD.ino
	but the .h & .cpp lets the main sketch code use this.
 */

#include "Arduino.h" // For Arduino functions like delay()
#include "BattleshipLCD.h"
#include "../PresentationAbstraction/GameEvent.h"

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

//---(Following are the PCF8574 pin assignments to LCD connections )----
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
/*-----( Declare Constants )-----*/

namespace BattleshipLCD {
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
/*-----( Declare Variables )-----*/
//NONE

/*-----( Declare Functions )-----*/
void eventLCD(const GameEvent input, const Position pos);
void instructUser();
void hit_();
void missed();
void sunk();
void endOfGame(int playerNo);
void highScore(int highSc);

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  listenForGameEvents(eventLCD);

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Welcome to your ");
  lcd.setCursor(0,1);
  lcd.print("Battleship game! ");
  delay(3000);
  lcd.clear();
}/*--(end setup )---*/

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
     case gameover:
      endOfGame(pos.x); // Assuming Player 1 won
      delay(3000);
      highScore(20);  // assuming high score(lowest number of turns needed to win game was 20)
  }
}

void instructUser() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter position");
  lcd.setCursor(0,1);
  lcd.print("to shoot (x,y)");
}

void hit_() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You hit ");
  lcd.setCursor(0,1);
  lcd.print("Go again. ");
}

void missed() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sorry! ");
  lcd.setCursor(0,1);
  lcd.print("You missed ");
}

void sunk() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Congratulations! ");
  lcd.setCursor(0,1);
  lcd.print("Ship sunk ");
}

void endOfGame(int x) {
  lcd.clear();
  playerNo = x;
  lcd.setCursor(0,0);
  lcd.print("Player: ");
  lcd.setCursor(8,0);
  lcd.print(x);
  lcd.setCursor(0,1);
  lcd.print("You win");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Victory!");
}
void highScore(int highSc) {
  lcd.clear();
  int x = highSc;
  lcd.setCursor(0,0);
  lcd.print("High Score: ");
  lcd.setCursor(0,1);
  lcd.print(x);
}
/* ( THE END ) */

}
