#include <Arduino.h>

const int ledPin = 2; // onboard LED, change if using external

void setup() {
  pinMode(ledPin, OUTPUT); // set LED pin as output
}

void loop() {
  digitalWrite(ledPin, HIGH); // LED ON
  delay(200);                 // wait 200 ms
  digitalWrite(ledPin, LOW);  // LED OFF
  delay(200);                 // wait 200 ms
}
