#include "libs/ic74hc595.h"

#define latchPin 8
#define clockPin 12
#define dataPin 11
#define LENGTH_LED 16
const int soundPin = A0;

ic74hc595 neo(latchPin, clockPin, dataPin);

int maxSound = 0;
int minSound;
int numsLED = 0;
int delayTime = 0;

void setup() {
  Serial.begin(9600);
  neo.ic74hc595Init();
  neo.setLength(LENGTH_LED);
  pinMode(soundPin, INPUT);
  delay(1000);
  Serial.println("Begin to collect range of sound!");
  for (int i = 0; i < 500; i++) {
    int sound = analogRead(soundPin);
    if (sound > maxSound) maxSound = sound;
    if (sound < minSound) minSound = sound;
    delay(10);
  }
  minSound = minSound + (maxSound - minSound) * 0.08;
  Serial.print("End! - Max: "); Serial.print(maxSound); Serial.print(" - Min: "); Serial.println(minSound);
}

void loop() {
  int sound = analogRead(soundPin);
  Serial.println(sound);
  numsLED = map(sound, minSound, maxSound, 0, 16);
  Serial.println(numsLED);
  delayTime = 96 - numsLED * 2;

  for (int i = 1; i <= numsLED; i++) {
  	neo.writeLED(i);
    delay(3);
  }
  for (int i = numsLED - 1; i >= 0; i--) {
  	neo.writeLED(i);
    delay(3);
  }
  delay(delayTime);
}