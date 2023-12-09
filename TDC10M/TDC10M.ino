#include <Arduino.h>
#include <SoftPWM.h>
#include <Ultrasonic.h>
char packet[1000] = { 0 };
uint32_t pins[10] = { 13, 5, 10, 9, 8, 6, 12, 4, 2, 3};
Ultrasonic ultrasonic(14, 16);
int distance = 0;

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
    //Serial.print(bytes);
    Serial.flush();
  } 
  for (int i=0; i<10; i++) {
      distance += ultrasonic.read();
      delay(10);
    }
  distance = distance = distance/10;
 // Serial.print("Distance in CM: ");
 // Serial.println(distance);
  if (distance < 150) {
    for (int a=0; a<10; a++) {
      SoftPWMSet(pins[a], (uint8_t)packet[a]);
    }
  } else {
      for (int a=0; a<10; a++) {
        SoftPWMSet(pins[a],0);
      }
  }
  delay(33);
}
