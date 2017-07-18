#include<Wire.h>

#define DEVICE_ADD 11

#define RED_LED_PIN 7
#define GRN_LED_PIN 8
#define BLU_LED_PIN 9
#define HIT_PIN     5

int hit=0;
byte MODE=16;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(DEVICE_ADD);
  //I2S Functions
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  //define leds
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GRN_LED_PIN, OUTPUT);
  pinMode(BLU_LED_PIN, OUTPUT);
  pinMode(HIT_PIN, INPUT);
}

void loop() {
  
  
  hit=digitalRead(HIT_PIN);
  
  if(MODE!=16){
  updateMODE(); }  
  delay(10);
  
}

void requestEvent() {
  Serial.println("HIT");
  //Send hit data on request
  Wire.write(hit);
   Serial.println(hit);
  hit=0;
}

void receiveEvent(int howMany){
  // reads the lights mode 
  MODE = Wire.read();
  Serial.println(MODE);
  }

void updateMODE(){

Serial.println(MODE);


bool red=MODE%2;
bool grn=(MODE/2)%2;
bool blu=(MODE/4)%2;

  if(red==1){
  digitalWrite(RED_LED_PIN,HIGH);
  }else{
  digitalWrite(RED_LED_PIN,LOW);
  }
  if(grn==1){
  digitalWrite(GRN_LED_PIN,HIGH);
  }else{
  digitalWrite(GRN_LED_PIN,LOW);
  }
  if(blu==1){
  digitalWrite(BLU_LED_PIN,HIGH);
  }else{
  digitalWrite(BLU_LED_PIN,LOW);
  }
  MODE=16;
}

