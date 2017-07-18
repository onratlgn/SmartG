#include "Arduino.h"
#include <Wire.h>
#define HIT_PIN     5
#define STEADY_STATE_MODE    16
class Slav {
public:

	Slav(int deviceAdd_);
	void begin();
	void requestEvent();
	void receiveEvent(int howMany);
	void updateMODE();
	void dontBlink();
	void getHit();
	void loop();

	int hit = 0;
	int loopDelay = 10;
	int blinkDelay = 100;
	int blinkRate;
	int deviceAdd;

	bool RGBcolorSpace[3] = { 0,0,0 };
	const int RGBcolorPins[3] = { 7,8,9 };

	bool bli = 0;//blink var
	bool blinkState = 0;//blink state
	int blinkCounter = 0;

	byte MODE = STEADY_STATE_MODE;// 
};
