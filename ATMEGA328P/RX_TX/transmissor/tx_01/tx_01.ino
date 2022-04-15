#include "SoftwareSerial.h" 

  SoftwareSerial mySerial(4,5); // (RX, TX)

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
    Serial.print("Transmissor");
}

void loop() {
  mySerial.write("Tales Cembraneli Dantas!");
  Serial.print(".");
  delay(200);
}
