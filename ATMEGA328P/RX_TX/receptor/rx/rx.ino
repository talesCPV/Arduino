#include "SoftwareSerial.h" 
  
    char ch;
    SoftwareSerial mySerial(2,3); // (RX, TX)

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);  
  pinMode(13, OUTPUT);  // configura o pino do LED como saida
  digitalWrite(13,LOW);
}

void loop() {

  if (mySerial.available()) {
    digitalWrite(13,HIGH);
    ch = mySerial.read ();
  }
  Serial.println(ch);
  
  digitalWrite(13,LOW);
  ch = "";


  

  //delay(20);
}
