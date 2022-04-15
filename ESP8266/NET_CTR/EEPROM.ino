/* EEPROM FUNCTIONS  */

/******* EEPROM MAP ********
ADDRES | BIT | DESCRIBE 
   0   |  0  | ROOT MODE
   0   |  1  | SERVER MODE
   1   | ALL | ENABLE DOORS
   2   | ALL | OUTPUT DOORS
****************************/

void rec_ram(int endereco, byte valor){
  Serial.println("REC EEPROM...");
  EEPROM.begin(4096);
  EEPROM.write(endereco, valor); 
  EEPROM.end();
}

byte read_ram(int endereco){
  Serial.println("READ EEPROM...");
  EEPROM.begin(4096);  
  int resp = EEPROM.read(endereco);
  EEPROM.end();
  return (byte)resp;
}

void writeBit(int adr, int pos,  int val){
  byte in = read_ram(adr);
  bitWrite(in, pos, val);
  EEPROM.begin(4096);
  EEPROM.write(adr, in);  
  EEPROM.end();    
}

int readBit(int adr, int pos){
  byte in = read_ram(adr);
  int out = bitRead(in, pos);
  return out;
   
}
