# HS-Int_Battleship
The Battleship game, using two Arduinos and 4 LED displays.

### Repo Format
This repo contains two sketches: Battleship & Controller2.
- Battleship is the main / "master" sketch. It runs all the game logic.
- Controller2 is an extra / "slave" sketch. It reads input from a Keypad & sends it to the main Arduino.
	- This should be run on a second Arduino.

_Note:_ Controller2 is optional. To run Battleship with one Arduino, use one of the other InputSources:
- KeypadInputSource: Can also read from a real Keypad
- SerialInputSource: Can read input from Serial Monitor
	- Each message should be in the format: x y
