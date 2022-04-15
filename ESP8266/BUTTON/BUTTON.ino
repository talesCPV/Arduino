#define BTN 14
#define LED 10

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(BTN,INPUT_PULLUP);
}

void loop() {
/*  
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
*/

  digitalWrite(LED,digitalRead(BTN));
/*
  if(digitalRead(BTN)){
    digitalWrite(LED,HIGH);
  }else{
    digitalWrite(LED,LOW);
  }
*/
}
