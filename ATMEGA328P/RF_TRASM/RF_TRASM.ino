// Pino do transmissor
#define TX 12
#define LED 13
#define BT 10

void setup() {
  pinMode(BT, INPUT);
  pinMode(TX, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // Coloca o pino TX em alta a cada x segundos
  if(digitalRead(BT)){
    digitalWrite(TX, HIGH);
    digitalWrite(LED, HIGH);    
  }else{
    digitalWrite(TX, LOW);
    digitalWrite(LED, LOW);    
  }
//  delay(3000);
//  delay(3000);
}
