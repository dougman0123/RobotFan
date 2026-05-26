#include <Wire.h>
#include "paj7620.h"

unsigned long lastForwardTime = 0;
bool waitingForPullback = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(20, 21);
  delay(500);
  if (paj7620Init() == 0) {
    Serial.println("PAJ7620 ready");
  } else {
    Serial.println("PAJ7620 init FAILED");
  }
}

void loop() {
  uint8_t data = 0;
  uint8_t data2 = 0;
  paj7620ReadReg(0x43, 1, &data);
  paj7620ReadReg(0x44, 1, &data2);

  if (data) {
    if (data & GES_FORWARD_FLAG) {
      waitingForPullback = true;
      lastForwardTime = millis();
      delay(200);
    }
    else if ((data & GES_BACKWARD_FLAG) && waitingForPullback && (millis() - lastForwardTime < 1000)) {
      Serial.println("Back/cancel");
      waitingForPullback = false;
      delay(800);
    }
    else if (data & GES_BACKWARD_FLAG) {
      // ignore raw backward
    }
    else {
      waitingForPullback = false;
      if (data & GES_RIGHT_FLAG)           { Serial.println("Right swipe");       delay(500); }
      if (data & GES_LEFT_FLAG)            { Serial.println("Left swipe");        delay(500); }
      if (data & GES_UP_FLAG)              { Serial.println("Up");                delay(500); }
      if (data & GES_DOWN_FLAG)            { Serial.println("Down");              delay(500); }
      if (data & GES_CLOCKWISE_FLAG)       { Serial.println("Clockwise");         delay(600); }
      if (data & GES_COUNT_CLOCKWISE_FLAG) { Serial.println("Counter-clockwise"); delay(600); }
    }
  }

  // forward alone = select (if no pullback within 1 second)
  if (waitingForPullback && (millis() - lastForwardTime >= 1000)) {
    Serial.println("Select");
    waitingForPullback = false;
    delay(800);
  }

  if (data2 & GES_WAVE_FLAG) { Serial.println("Wake"); delay(1000); }
  delay(100);
}
