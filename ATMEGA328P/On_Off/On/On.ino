void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
}

void loop() {
  delay(1000);
  digitalWrite(2,!digitalRead(2));
}
