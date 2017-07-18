#include <Slav.h>
#define DeviceAdd 11

Slav Slave(11); 

void setup() {
  Serial.begin(9600);
  Slave.begin();
  Wire.onRequest(Slave.requestEvent);
  Wire.onReceive(Slave.receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  Slave.loop();
}
