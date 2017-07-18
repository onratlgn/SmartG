//       ____
//      /    \    
//     /  /\  \    Ali KESGİN
//    /  /  \  \	Robota
//   /  /    \  \________
//  /  /      \___________
#include "Slav.h"

Slav::Slav(int deviceAdd_) {
	deviceAdd = deviceAdd_;
}

void Slav::begin() {

	Wire.begin(DEVICE_ADD);
	//I2S Functions
	Wire.onRequest(void requestEvent);
	Wire.onReceive(void receiveEvent);
	//define led pins
	pinMode(RGBcolorPins[0], OUTPUT);
	pinMode(RGBcolorPins[1], OUTPUT);
	pinMode(RGBcolorPins[2], OUTPUT);
	pinMode(HIT_PIN, INPUT);

	blinkRate = blinkDelay / loopDelay;
}

void Slav::requestEvent() {
	Serial.println("HIT");
	//Send hit data on request
	Wire.write(hit);
	Serial.println(hit);
	hit = 0;
}
void Slav::receiveEvent(int howMany) {
	// reads the lights mode 
	MODE = Wire.read();
	Serial.println(MODE);
}
void Slav::updateMODE() {

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

	MODE = STEADY_STATE_MODE;// the recieved mode applied there is no mode to apply
}
void Slav::dontBlink() {
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
void Slav::getHit() {
	hit = digitalRead(HIT_PIN);
}
void Slav::loop() {
	getHit();
	if (MODE != STEADY_STATE_MODE) {
		updateMODE();
	}
	dontBlink();
	delay(loopDelay);
}
