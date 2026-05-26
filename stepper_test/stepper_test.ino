#define STEP_PIN 5
#define DIR_PIN  6

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  Serial.begin(115200);
}

void step(int steps, bool dir, int delayUs) {
  digitalWrite(DIR_PIN, dir);
  delayMicroseconds(2);
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delayUs);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayUs);
  }
}

void loop() {
  step(400, HIGH, 1000);
  delay(500);
  step(400, LOW, 1000);
  delay(500);
}
