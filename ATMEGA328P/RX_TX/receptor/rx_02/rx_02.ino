#include "SoftwareSerial.h" 
      
  SoftwareSerial mySerial(2,3); // (RX, TX)

  String ret = "";
  int i = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);  
  pinMode(13, OUTPUT);  // configura o pino do LED como saida
  digitalWrite(13,LOW);
  Serial.print("Receptor");
}

void loop() {
  ret = "";

  
  while (mySerial.available()) {
    digitalWrite(13,HIGH);
    ret += mySerial.read();
       
  }

  Serial.println("->"+ret);
  
  digitalWrite(13,LOW);

delay(500);

}
