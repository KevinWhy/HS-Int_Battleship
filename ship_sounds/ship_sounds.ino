

int speakerPin = 8;

enum GameEvent {
  hit, miss, sinking // Example events
};


void setup() {
  pinMode(speakerPin, OUTPUT); // sets the speakerPin to be an output 
  eventSound(sinking); 
}

void loop()
{
  // do nothing
}

void eventSound(GameEvent input) {
  
  switch (input){
    case hit:
      hit_();
      break;
    case miss:
      missed();
      break;
    case sinking:
      sinked();
      break;
  }    
}

void missed() {
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

void hit_() {
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

