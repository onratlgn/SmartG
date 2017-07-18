#include<Wire.h>

#define DEVICE_ADD 12

const int SLAVE_NUM = 2;

// initialize SLAVE data
const int SLAVE_ADD[SLAVE_NUM] = { 10, 11 };

byte SLAVE_DATA[SLAVE_NUM] = { 0,0 };
byte SLAVE_DATA_OLD[SLAVE_NUM] = { 0,0 };
bool SLAVE_HIT[SLAVE_NUM] = { 0,0 };

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Wire.begin(DEVICE_ADD);
}

void loop() {

	getHITDATA();

	UPDATE_TABLE();

	PUB_TABLE();

	delay(500);

	Serial.println("LOOP DONE");

}

void getHITDATA() {

	Serial.println("GET HIT DATA");
	int i;

	for (i = 0; i<SLAVE_NUM; i++) {

		Wire.requestFrom(SLAVE_ADD[i], 1);
		while (Wire.available()) {
			SLAVE_HIT[i] = Wire.read();
		}
		delay(10);
		Serial.println(SLAVE_HIT[i]);
	}
}

void UPDATE_TABLE() {
	int i = 0;
	for (i = 0; i<SLAVE_NUM; i++) {
		if (SLAVE_HIT[i] == 1) {
			SLAVE_DATA[i]++;
			if (SLAVE_DATA[i] == 8) {
				SLAVE_DATA[i] = 0;
			}
			SLAVE_HIT[i] = 0;
		}
	}
	Serial.println("TABLE UPDATED");
}

void PUB_TABLE() {
	int i;
	for (i = 0; i<SLAVE_NUM; i++) {
		if (SLAVE_DATA[i] != SLAVE_DATA_OLD[i]) {

			Serial.println("CHANGE");
			Serial.println(SLAVE_ADD[i]);
			Wire.beginTransmission(SLAVE_ADD[i]);
			Wire.write(SLAVE_DATA[i]);
			Wire.endTransmission();
			delay(10);
			SLAVE_DATA_OLD[i] = SLAVE_DATA[i];


		}
	}
}
