/* Battleship using arduinos and 8x8 led matrix MAX7219

   Has a demo of:
   - Input Abstraction
       You can use SerialInput (default) or KeypadInput.
   - Presentation Abstraction (aka: GameEvent listeners)
       Two functions respond to game "Ticks" & inputs.
*/

#include "Abstract.h"
#include "Board.h"
//#include "src/ShipSound/ship_sounds.h"
//#include "src/BattleshipLCD/BattleshipLCD.h"
#include "src/PresentationAbstraction/GameEvent.h"

#include "src/InputAbstraction/SerialInputSource.h"
#include "src/InputAbstraction/KeypadInputSource.h"
// To use KeypadInputSource, need to specify where it uses a Keypad or an Arduino
//#include "src/InputAbstraction/KeypadInterface/PhysicalKeypad.h"
#include "src/InputAbstraction/KeypadInterface/ArduinoKeypad.h"
#include "LedControl.h" //  need the library
//#include <Keypad.h>
/*#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
*/
///lcd part yo
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

/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
/*-----( Declare Variables )-----*/
//NONE

/*-----( Declare Functions )-----*/
//void eventLCD(const GameEvent input, const Position pos);
//void instructUser();
//void hit_();
//void missed();
//void sunk();
//void endOfGame(int x);
//void highScore(int highSc);

LedControl lc = LedControl(9,7,6,4); //

//variables to store the score for each player
//both score variables are incremented each time the corresponding player takes a turn
//when the game ends, if the score of the winning player is less than the previous HighScore
//the previous HighScore is replaced.
int p1_score = 0;
int p2_score = 0;

//speaker pin
int speakerPin = 8;

//prototypes 
Position* shipPlacement(int, Board&, InputSource*, LedControl);
bool checkHit(int, int, Board*, Ship*, Ship*, Ship*);
bool playerLose(Ship, Ship, Ship);
//void hit_();
void eventSound(const GameEvent, const Position);
void eventLCD(const GameEvent, const Position);
void instructUser();

//bool values to step move forward with the program once the ships are placed
bool p1_placed = false;
bool p2_placed = false;

//the display boards
Board ship_board1(0);
Board ship_board2(2);

Board* board1 = &ship_board1;
Board* board2 = &ship_board2;
/********************************/
//ship objects
Ship carrier(true, 5);
Ship battleship(true, 4);
Ship cruiser(true, 3);

Ship* carrier1 = &carrier;
Ship* battleship1 = &battleship;
Ship* cruiser1 = &cruiser;

Ship carrier_2(true, 5);
Ship battleship_2(true, 4);
Ship cruiser_2(true, 3);

Ship* carrier2 = &carrier_2;
Ship* battleship2 = &battleship_2;
Ship* cruiser2 = &cruiser_2;
// Define keypad for KeypadInputSource
//const byte rowPins[KPD_ROWS] = {8, 7, 6, 5};
//const byte colPins[KPD_COLS] = {12, 11, 10, 9};
//PhysicalKeypad keypd1(rowPins, colPins);
// Use Arduino for KeypadInputSource
const byte arduino_rxPin = 2;
const byte arduino_txPin = 4;
ArduinoKeypad keypd(arduino_rxPin, arduino_txPin);
// Use some keypad as InputSource
//InputSource* player2 = new KeypadInputSource(&keypd);
//InputSource* player1 = new KeypadInputSource(&keypd);

// Use SerialInput
InputSource* player1 = new SerialInputSource();
InputSource* player2 = new SerialInputSource();

/* This function is called when the player is planning to send a different input.
   However, they may change it a few more times before actually sending input.
   Should be used for presenting input as it changes (on LCD display)?
*/
/*void onKeypadChange(Position currPos) {
  // For now, just print the position the player is considering
  Serial.print(F("\t\tmaybe... ("));
  Serial.print(currPos.x);
  Serial.print(F(","));
  Serial.print(currPos.y);
  Serial.println(F(")"));
}*/

/********************************/

void setup() {
  // Example: Create some ships
  for(int i = 0; i < 4; ++i)
  {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
  
  Serial.begin(9600);
  //ShipSound::setup();
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Welcome to your ");
  lcd.setCursor(0,1);
  lcd.print("Battleship game! ");
  delay(3000);
  lcd.clear();
  
  pinMode(speakerPin, OUTPUT);
  //Position posArray[shipMaxSize]; // store coordinates in posArray to be set by shipInit
  //shipInit(&carrier, posArray);

  // Input Abstraction demo...
  
  //player2->onInputChange(onKeypadChange); // Bind function to when input changes
  //player1->onInputChange(onKeypadChange());

  // Have two functions listen for the DEBUG GameEvents
  //listenForGameEvents(onGameEventPrint);
  //listenForGameEvents(dullListener);
}

void(* resetFunc) (void) = 0; 

void loop() {
  //player2->loop();

//   When input has been read...
  Serial.print(F("loop reached"));
  //display welcome screen


  while(!p1_placed || !p2_placed)
  {
    instructPlaceShip();
    shipInit(&carrier, shipPlacement(5, ship_board1, player1, lc));
    lc.clearDisplay(0);
    lc.clearDisplay(1);
    ship_board1.display(lc);
    shipsPlaced();
    Serial.println(F("yey! first ship placed"));
    
    instructPlaceShip();
    shipInit(&battleship, shipPlacement(4, ship_board1, player1, lc));
    lc.clearDisplay(0);
    lc.clearDisplay(1);
    ship_board1.display(lc);
    shipsPlaced();
    
    instructPlaceShip();
    shipInit(&cruiser, shipPlacement(3, ship_board1, player1, lc));
    lc.clearDisplay(0);
    lc.clearDisplay(1);
    ship_board1.display(lc);
    shipsPlaced();

    instructPlaceShip();
    shipInit(&carrier_2, shipPlacement(5, ship_board2, player2, lc));
    lc.clearDisplay(2);
    lc.clearDisplay(3);
    ship_board2.display(lc);
    shipsPlaced();

    instructPlaceShip();
    shipInit(&battleship_2, shipPlacement(4, ship_board2, player2, lc));
    lc.clearDisplay(2);
    lc.clearDisplay(3);
    ship_board2.display(lc);
    shipsPlaced();

    instructPlaceShip();
    shipInit(&cruiser_2, shipPlacement(3, ship_board2, player2, lc));
    //ship_board2.printa();
    lc.clearDisplay(2);
    lc.clearDisplay(3);
    ship_board2.display(lc);
    shipsPlaced();

    int check1 = ship_board1.getNumberOfPos();
    int check2 = ship_board2.getNumberOfPos();
    
    //Serial.print(check2);
    //Serial.println(check1);
    
    if(check1 == 12 && check2 == 12)
    {
      p1_placed = true;
      p2_placed = true;
    }
  }

  // This is where the users turns begin
  // The while loop runs until lose is set to true by the playerLose function
    
  while(Serial.available() > 0) {
        char t = Serial.read();
    }
  
  bool lose = false;
  bool game_over = false;
  
  while(game_over == false)
  {
    while(!player1->hasInput())
      {
        player1->loop();
        lc.clearDisplay(0);
        lc.clearDisplay(1);
        ship_board1.display(lc);
        lc.clearDisplay(2);
        lc.clearDisplay(3);
        ship_board2.display(lc);
        //ship_board2.display(lc);
        instructUser();  
      }
      
    Position pos = player1->getNextPos();

    // Print
    
    
    bool hitCheck = checkHit(pos.y - 1, pos.x - 1, board2, carrier2, battleship2, cruiser2);
    //Serial.println(hitCheck);

    //ship_board1.printa();
    //ship_board2.printa();

    ++p1_score;
    
    /*
    for(int j = 0; j < 6; j++)
    {
      Serial.println(board2->Pos[j].hitMarker);
      Serial.print(board2->Pos[j].x);
      Serial.println(board2->Pos[j].y);
    }
    */
    
    bool car_sunk = carrier2->checkShipSunkandUpdateState();
    bool bat_sunk = battleship2->checkShipSunkandUpdateState();       //a check to see if any of the ships have sunk
    bool cru_sunk = cruiser2->checkShipSunkandUpdateState();
    //Serial.println("aaaa");
    //Serial.println(cru_sunk);

    if(hitCheck == true)
    {
      //fireGameEvent(hit, pos);
      a_hit();
      hit_();
      //delay(2000);
    }
    else
    {
      //const GameEvent j = miss;
      //eventSound(j, INVALID_POS);
      //eventLCD(j, INVALID_POS);
      a_miss();
      missed();
      delay(2000);
    }
    
    if(car_sunk == true)
    {
      //fireGameEvent(sink, INVALID_POS); //player2s lcd screen
      sinked();
      sunk();
    }
    if(bat_sunk == true)
    {
      //fireGameEvent(sink, INVALID_POS); //player2s lcd screen
      sinked();
      sunk();
    }
    if(cru_sunk == true)
    {
      //fireGameEvent(sink, INVALID_POS); //player2s lcd screen
      sinked();
      sunk();
    }
    
      
         
    lose = playerLose(carrier_2, battleship_2, cruiser_2);
    if(lose == true)
    {
      //Position aPOS = {2, 0};
      //fireGameEvent(player_Loss, aPOS);
      endOfGame(1); 
      game_over = true;
      break;
    }
    
     while(Serial.available() > 0) {
        char t = Serial.read();
    }
     
     while(!player2->hasInput())
     {
        player2->loop();
        lc.clearDisplay(0);
        lc.clearDisplay(1);
        ship_board1.display(lc);
        lc.clearDisplay(2);
        lc.clearDisplay(3);
        ship_board2.display(lc);  
        instructUser();
     }
      
      Position pos2 = player2->getNextPos();
      bool hitCheck2 = checkHit(pos2.y - 1, pos2.x - 1, board1, carrier1, battleship1, cruiser1);

      ship_board1.printa();
      ship_board2.printa();
    
      ++p2_score;
      bool car_sunk2 = carrier.checkShipSunkandUpdateState();
      bool bat_sunk2 = battleship.checkShipSunkandUpdateState();
      bool cru_sunk2 = cruiser.checkShipSunkandUpdateState();
      if(hitCheck2 == true)
      {
        a_hit();
        hit_();
        //delay(2000);
      } 
      else
      {
        a_miss();
        missed();
        delay(2000);        
      }

        
      if(car_sunk2 == true)
      {
        //fireGameEvent(sink, INVALID_POS); //player1s lcd screen
        sinked();
        sunk();
      }
      if(bat_sunk2 == true)
      {
        //fireGameEvent(sink, INVALID_POS); //player1s lcd screen
        sinked();
        sunk();
      }
      if(cru_sunk2 == true)
      {
        //fireGameEvent(sink, INVALID_POS); //player1s lcd screen
        sinked();
        sunk();
      }
      
      
      lose = playerLose(carrier, battleship, cruiser);
      if(lose == true)
      {
        //Position aPOS = {1, 0};
        //fireGameEvent(player_Loss, aPOS);
        endOfGame(2);
        game_over = true;
        break;
      }

      
    }
  

  
}

void instructUser() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter position");
  lcd.setCursor(0,1);
  lcd.print("to shoot (x,y)");
}
void instructPlaceShip() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place a ship");
}
void shipsPlaced() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ship Placed");
  delay(2000);
}


void hit_() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("There was a hit ");
  delay(2000);
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
  delay(2000);
}

void endOfGame(int x) {
  lcd.clear();
  int playerNo = x;
  lcd.setCursor(0,0);
  lcd.print("Player: ");
  lcd.setCursor(8,0);
  lcd.print(playerNo);
  lcd.setCursor(0,1);
  lcd.print("You win");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Victory!");
  delay(2000);
}
void highScore(int highSc) {
  lcd.clear();
  int x = highSc;
  lcd.setCursor(0,0);
  lcd.print("High Score: ");
  lcd.setCursor(0,1);
  lcd.print(x);
}
void a_miss() {
  for (int i=1000; i<5000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
 delay(100);

  for (int i=1000; i<3000; i=i*1.03) {
    beep(speakerPin,i,10);
  }
  for (int i=5000; i>1000; i=i*.97) {
    beep(speakerPin,i,10);
  }
}

void a_hit() {
  for (int i=1000; i<2000; i=i*1.02) {
    beep(speakerPin,i,10);
  }
  for (int i=2000; i>1000; i=i*.98) {
    beep(speakerPin,i,10);
  }
  for(int i=0; i<6 ; i++){
    ping(i*5);
  }
}

void sinked(){
  for(int i=0; i<7 ; i++){
    ping(i*40);
  }
}


void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{
          int x;
          long delayAmount = (long)(1000000/frequencyInHertz);
          long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
          for (x=0;x<loopTime;x++)
          {
              digitalWrite(speakerPin,HIGH);
              delayMicroseconds(delayAmount);
              digitalWrite(speakerPin,LOW);
              delayMicroseconds(delayAmount);
          }

}

void ping(int dly) {
       beep(speakerPin,100,50);
       delay(dly);
       beep(speakerPin,100,50);
       delay(dly);
       beep(speakerPin,100,50);
       delay(dly);
}

