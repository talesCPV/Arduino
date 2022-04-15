
byte flag = 0x00;

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.println("INICIO");

  setBit(&flag,3);
  Serial.println(readBit(flag,3));
  clearBit(&flag,3);
  Serial.println(readBit(flag,3));

  
  for(int i=0; i<8; i++){
    Serial.print(i);
    Serial.print(" result flag -> ");
    Serial.println(readBit(0xB5,i));    
  }

  Serial.println("FINAL");
  
}

void loop() {


}

boolean readBit( byte FLAG, int POS){ 
  FLAG = FLAG >> POS; // PUT NEED POS IN FIRST BIT
  FLAG = FLAG & 0x01; // APPLY MASK IN FIRST POS
  return FLAG;        // RETURN BOOLEAN VALUE
}

byte setBit(byte *FLAG, int POS){
  byte MASK = 0x01;   // MASK IN FIRST POS
  MASK = MASK << POS; // RUN MASK TO NEED POS
  *FLAG = *FLAG | MASK; // APPLY MASK INTO VALUE
}

byte clearBit(byte *FLAG, int POS){
  byte MASK = 0x01;   // MASK IN FIRST POS
  MASK = MASK << POS; // RUN MASK TO NEED POS
  MASK = MASK ^ 0xFF; // INVERT MASK
  *FLAG = *FLAG & MASK; // APPLY MASK INTO VALUE
}

/*
byte setBit(byte FLAG, int POS){
  byte MASK = 0x01;   // MASK IN FIRST POS
  MASK = MASK << POS; // RUN MASK TO NEED POS
  FLAG = FLAG | MASK; // APPLY MASK INTO VALUE
  return FLAG;        // RETURN VALUE
}

byte clearBit(byte FLAG, int POS){
  byte MASK = 0x01;   // MASK IN FIRST POS
  MASK = MASK << POS; // RUN MASK TO NEED POS
  MASK = MASK ^ 0xFF; // INVERT MASK
  FLAG = FLAG & MASK; // APPLY MASK INTO VALUE
  return FLAG;        // RETURN VALUE
}
*/
