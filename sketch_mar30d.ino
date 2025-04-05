const int timerOutputPin = 8; // Connected to Pin 7 of the 556 timer
unsigned long pulseDuration;

void setup() {
  pinMode(timerOutputPin, INPUT);
  Serial.begin(9600); // Open serial monitor
}

void loop() {
  // Wait for a HIGH pulse from the 556 output
  pulseDuration = pulseIn(timerOutputPin, HIGH);

  if (pulseDuration > 0) {
    Serial.print("Pulse Duration: ");
    Serial.print(pulseDuration);
    Serial.println(" microseconds");
  }

  delay(1000); // Small delay for readability
}
