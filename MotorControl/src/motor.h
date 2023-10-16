#include <Arduino.h>
#include <SoftPWM.h>
char packet[2000] = { 0 };
uint32_t pins[20] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 
					 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };

void setup() {
	SoftPWMBegin();
	SoftPWMSetFadeTime(ALL, 0, 0);
	Serial.begin(57600);
	Serial.setTimeout(100); // default is 1000
}

void loop() {
	int bytes = Serial.available();
	if (bytes) {
		// if (bytes < 23) 
		// int res = Serial.readBytes(packet, bytes);
		Serial.readBytes(packet, bytes);
		// Serial.print(bytes);
		Serial.flush();
	} 
	for (int a=0; a<20; a++) {
		SoftPWMSet(pins[a], (uint8_t)packet[a]);
	}
	delay(33);
}