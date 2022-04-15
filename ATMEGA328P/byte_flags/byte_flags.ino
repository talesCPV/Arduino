
byte teste = 0x00;

void setup() {
  Serial.begin(9600);
  Serial.println();

  Serial.println("INICIO");

  setBit(&teste,2);
  setBit(&teste,1);
  Serial.print("set -> ");    
  Serial.println(teste);    
 
  clearBit(&teste,2);
  Serial.print("clear -> ");    
  Serial.println(teste);    


  Serial.println("FINAL");
  
}

void loop() {


}

boolean readBit( byte FLAG, int POS){ 
  FLAG = FLAG >> POS; // PUT NEED POS IN FIRST BIT
  FLAG = FLAG & 0x01; // APPLY MASK IN FIRST POS
  return FLAG;        // RETURN BOOLEAN VALUE
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
