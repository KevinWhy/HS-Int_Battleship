/* Battleship using arduinos and 8x8 led matrix MAX7219

   Has a demo of:
   - Input Abstraction
       You can use SerialInput (default) or KeypadInput.
   - Presentation Abstraction (aka: GameEvent listeners)
       Two functions respond to game "Ticks" & inputs.
*/

#include "Abstract.h"
#include "Board.h"

#include "src/PresentationAbstraction/GameEvent.h"

#include "src/InputAbstraction/SerialInputSource.h"
#include "src/InputAbstraction/KeypadInputSource.h"
// To use KeypadInputSource, need to specify where it uses a Keypad or an Arduino
#include "src/InputAbstraction/KeypadInterface/PhysicalKeypad.h"
#include "src/InputAbstraction/KeypadInterface/ArduinoKeypad.h"
#include "LedControl.h" //  need the library
#include <Keypad.h>
LedControl lc = LedControl(8,7,6,1); //

//variables to store the score for each player
//both score variables are incremented each time the corresponding player takes a turn
//when the game ends, if the score of the winning player is less than the previous HighScore
//the previous HighScore is replaced.
int p1_score = 0;
int p2_score = 0;

//speaker pin
int speakerPin = 8;

//prototypes 
Position* shipPlacement(int, Board, InputSource*, LedControl);
bool checkHit(int, int, Board*, Ship*, Ship*, Ship*);
bool playerLose(Ship, Ship, Ship);

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
//const byte arduino_rxPin = 4;
//const byte arduino_txPin = 5;
//ArduinoKeypad keypd(arduino_rxPin, arduino_txPin);
// Use some keypad as InputSource
//InputSource* player2 = new KeypadInputSource(&keypd);
//InputSource* player1 = new KeypadInputSource(&keypd1);

// Use SerialInput
InputSource* player1 = new SerialInputSource();
InputSource* player2 = new SerialInputSource();

/* This function is called when the player is planning to send a different input.
   However, they may change it a few more times before actually sending input.
   Should be used for presenting input as it changes (on LCD display)?
*/
void onKeypadChange(Position currPos) {
  // For now, just print the position the player is considering
  Serial.print("\t\tmaybe... (");
  Serial.print(currPos.x);
  Serial.print(",");
  Serial.print(currPos.y);
  Serial.println(")");
}

/********************************/

void setup() {
  // Example: Create some ships
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  
  lc.clearDisplay(0);

  pinMode(speakerPin, OUTPUT); // sets the speakerPin to be an output 
  
  Serial.begin(9600);
  
  /*while(true){
    Serial.println("in Loop");
    lc.setLed(0, 3, 4, true);
  }*/
  //Position posArray[shipMaxSize]; // store coordinates in posArray to be set by shipInit
  //shipInit(&carrier, posArray);

  // Input Abstraction demo...
  
  //player2->onInputChange(onKeypadChange); // Bind function to when input changes
  //player1->onInputChange(onKeypadChange());

  // Have two functions listen for the DEBUG GameEvents
  //listenForGameEvents(onGameEventPrint);
  //listenForGameEvents(dullListener);
}

unsigned long ev_msCount = millis(); // Used for example GameEvent: EV_Ticker
void loop() {
  //player2->loop();

  // When input has been read...

  //display welcome screen


  while (p1_placed == false || p2_placed == false)
  {
    shipInit(&carrier, shipPlacement(5, ship_board1, player1, lc));
    Serial.println("first placed");
    shipInit(&battleship, shipPlacement(4, ship_board1, player1, lc));
    shipInit(&cruiser, shipPlacement(3, ship_board1, player1, lc));

    shipInit(&carrier_2, shipPlacement(5, ship_board2, player2, lc));
    shipInit(&battleship_2, shipPlacement(4, ship_board2, player2, lc));
    shipInit(&cruiser_2, shipPlacement(3, ship_board2, player2, lc));

    int check1 = ship_board1.getNumberOfPos();
    int check2 = ship_board2.getNumberOfPos();

    if (check1 == 12 && check2 == 12)
    {
      p1_placed == true;
      p2_placed == true;
    }
  }

  // This is where the users turns begin
  // The while loop runs until lose is set to true by the playerLose function
    
  bool lose = false;

  while(lose == false)
  {
    while(!player1->hasInput())
      {
        //player1->loop();  
      }
      
    Position pos = player1->getNextPos();
    bool hitCheck = checkHit(pos.y - 1, pos.x - 1, board2, carrier2, battleship2, cruiser2);
    ++p1_score;
    /*if(hitCheck == true)
      //fireGameEvent(hit);
    else
      //fireGameEvent(miss);
     */     
    lose = playerLose(carrier_2, battleship_2, cruiser_2);
    
    while(lose == false)
    {
      while(!player2->hasInput())
      {
        //player2->loop();  
      }
      
      Position pos2 = player2->getNextPos();
      bool hitCheck2 = checkHit(pos2.y - 1, pos2.x - 1, board1, carrier1, battleship1, cruiser1);
      ++p2_score;
      /*
      if(hitCheck == true)
        //fireGameEvent(hit);
      else
        //fireGameEvent(miss);
      */
      lose = playerLose(carrier, battleship, cruiser);
    }
  }

  //player1->loop();



  // Every 3 seconds, fire EV_Ticker (Example GameEvent)
  /*if (millis() - ev_msCount > 3000) {
    fireGameEvent(EV_Ticker, INVALID_POS);
    ev_msCount = millis();
  }*/
}
