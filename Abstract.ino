/* Battleship using arduinos and 8x8 led matrix MAX7219 */

int const shipMaxSize = 5;

struct Position{
  int x;
  int y;
};

class Ship {
  private:
    Position Pos[shipMaxSize];
    bool state; // sunken or not true = float; false = sunken
    int shipSize; // size of ship

  public:
    Ship();
    Ship(bool shipSt, int shipSi);
    void setPos(int index, int xPos, int yPos);
    Position getPos(){return *Pos;};
    int getSize(){return shipSize;}
};

void Ship::setPos(int index, int xPos, int yPos){
  Pos[index].x = xPos;
  Pos[index].y = yPos; 
}

Ship::Ship(){
}

Ship::Ship(bool shipSt, int shipSi){
  state = shipSt;
  shipSize = shipSi;
}

void shipInit(Ship *ship, Position posArr[]){
  for(int i = 0; i < ship->getSize(); i++){
    ship->setPos(i, posArr[i].x, posArr[i].y);
  }
}

void setup() {
  Ship carrier(true,5);
  Ship battleship(true,4);
  Ship cruiser(true,3);
  Ship submarine(true,3);
  Ship destroyer(true,2;

  Position posArray[shipMaxSize]; // store coordinates in posArray to be set by shipInit
  shipInit(&carrier, posArray);
}

void loop() {
  // put your main code here, to run repeatedly:
}
