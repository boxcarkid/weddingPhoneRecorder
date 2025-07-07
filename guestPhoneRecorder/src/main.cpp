#include <Arduino.h>

const int ledPin = 13; // Built-in LED is on pin 13

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=246,460
AudioOutputI2S           i2s1;           //xy=707,477
AudioConnection          patchCord1(playSdWav2, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav2, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=411,536
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  // Audio connections require memory to work
  AudioMemory(8);
  
  // Initialize the audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(.5); // Set volume to 50%
  
  // Configure line output specifically
  sgtl5000_1.lineOutLevel(13); // Set line output level (0-31, 13 is about 1.29V RMS)
  sgtl5000_1.audioPostProcessorEnable(); // Enable audio post-processor for better quality
  
  // Initialize SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    Serial.println("Unable to access the SD card");
    while(1); // Stop here if SD card can't be accessed
  }
  
  Serial.println("Starting - Audio system initialized");
}

void loop() {
  Serial.println("LED ON");
  digitalWrite(ledPin, HIGH);
  
  if (playSdWav2.isPlaying() == false) {
    Serial.println("Starting audio playback");
    if (playSdWav2.play("phillTestAudio.wav")) {
      Serial.println("Audio file started successfully");
    } else {
      Serial.println("Error: Could not start audio file");
    }
    delay(10);
  } else {
    Serial.println("Audio is still playing");
  }
  
  delay(500); // Keep the LED on for 500 ms
  Serial.println("LED OFF");   
  digitalWrite(ledPin, LOW);
  delay(500);
}