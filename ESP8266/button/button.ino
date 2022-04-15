#define BTN_CONF 10

void setup() {
/******  START CPU  ******/  
  Serial.begin(115200);
  Serial.println();
  delay(200);
  
  pinMode(BTN_CONF, INPUT_PULLUP);

}

void loop() {

  if(digitalRead(BTN_CONF) == LOW){
    Serial.println("click");
    delay(100);
  }

}
