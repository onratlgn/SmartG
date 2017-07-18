#include<Wire.h>

#define DEVICE_ADD 11

#define HIT_PIN     5

int hit= 0;
int loopDelay = 10;
int blinkDelay = 100;
int blinkRate;

bool RGBcolorSpace[3]= { 0,0,0 };
const int RGBcolorPins[3] = { 7,8,9 };

bool bli = 0;//blink var
bool blinkState = 0;//blink state
int blinkCounter = 0;

byte MODE = 16;// 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(DEVICE_ADD);
  //I2S Functions
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  //define led pins
  pinMode(RGBcolorPins[0], OUTPUT);
  pinMode(RGBcolorPins[1], OUTPUT);
  pinMode(RGBcolorPins[2], OUTPUT);
  pinMode(HIT_PIN, INPUT);

  blinkRate = blinkDelay / loopDelay;

}

void loop() {

 getHit();

  if (MODE != 16) {
    updateMODE();
  }
  // blink
  dontBlink();

  delay(loopDelay);

}

void requestEvent() {
  Serial.println("HIT");
  //Send hit data on request
  Wire.write(hit);
  Serial.println(hit);
  hit = 0;
}

void receiveEvent(int howMany) {
  // reads the lights mode 
  MODE = Wire.read();
  Serial.println(MODE);
}

void updateMODE() {

  Serial.println(MODE);

  // decode recieved message
  RGBcolorSpace[0] = MODE % 2;
  RGBcolorSpace[1] = (MODE / 2) % 2;
  RGBcolorSpace[2] = (MODE / 4) % 2;
  bli = (MODE / 8) % 2;
  // apply changes
  int i;
  for (i = 0; i < 3; i++) {
    if (RGBcolorSpace[i] == 1) {
      digitalWrite(RGBcolorPins[i], HIGH);
    }
    else {
      digitalWrite(RGBcolorPins[i], LOW);
    }
  }

  MODE = 16;// the recieved mode applied there is no mode to apply
}

void dontBlink() {
  blinkCounter++;
  if (bli == 1 && blinkCounter > blinkRate) {
    // blink code runs here
    if (blinkState == 0) {
      // set them all to 0
      int i;
      for (i = 0; i < 3; i++) {
        digitalWrite(RGBcolorPins[i], LOW);
      }
    }
    else {
      // set them to their original state
      int i;
      for (i = 0; i < 3; i++) {
        if (RGBcolorSpace[i] == 1) {
          digitalWrite(RGBcolorPins[i], HIGH);
        }
        else {
          digitalWrite(RGBcolorPins[i], LOW);
        }
      }
    }
    blinkState = !blinkState;
    blinkCounter = 0;
  }
}
void getHit(){
    hit = digitalRead(HIT_PIN);
}

