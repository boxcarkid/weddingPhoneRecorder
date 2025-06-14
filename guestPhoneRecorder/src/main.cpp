#include <Arduino.h>

const int ledPin = 13; // Built-in LED is on pin 13

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.println("Starting LED Blink Example");
}

void loop() {
  Serial.println("LED ON");
  digitalWrite(ledPin, HIGH);
  delay(500);              
  Serial.println("LED OFF");   
  digitalWrite(ledPin, LOW);
  delay(500);
}