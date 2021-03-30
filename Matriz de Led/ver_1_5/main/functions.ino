

void setup() {
    
  ascii_begin();

  // Configura e inicializa cada bloco de Led da Matriz
  matrizLed.shutdown(0, false);
  matrizLed.setIntensity(0, 1);
  matrizLed.clearDisplay(0);

  matrizLed.shutdown(1, false);
  matrizLed.setIntensity(1, 1);
  matrizLed.clearDisplay(1);

  matrizLed.shutdown(2, false);
  matrizLed.setIntensity(2, 1);
  matrizLed.clearDisplay(2);

  matrizLed.shutdown(3, false);
  matrizLed.setIntensity(3, 1);
  matrizLed.clearDisplay(3);

  delay(100);

}

void loop() {
  
  cont++;
  if(cont == 8){
    cont = 0;
    getLetter(int(frase[index]));
    index++;
    if(index == frase.length()){
      index = 0;
    }
  }
  
  show_text();
  scroll();

  delay(SCROLL_SPEED);
  

}


void getLetter(int ASC){
  int i;
  for(i=0; i<8; i++){
    disp[4][i] = ascii[ASC-32][i];
  }  
}

void scroll(){
  int i;
  for(i=0; i<5; i++){
      scroll_block(i);
  }
}

void scroll_block(int block){
  int i;
  for(i=0; i<8; i++){
      disp[block][i] = disp[block][i] << 1;
      if(block < 4){
        bitWrite(disp[block][i], 0, bitRead(disp[block+1][i], 7));
      }else{
        bitWrite(disp[block][i], 0, 0);
      }
  }
}

void show_text(){
    int i;
  for(i=0; i<4; i++){
    imprimeBloco(i, disp[i]);  
  }
}

void imprimeBloco(int lcd, byte character [])
{
  int i;
  for (i = 0; i < 8; i++)
  {
    matrizLed.setRow(lcd, 7-i, inverte_byte(character[i]));
  }
}

byte inverte_byte(byte A){
  byte B;  
  int i;
  for(i=0; i<8; i++){
    bitWrite(B, i, bitRead(A, 7-i));
  }
  return B;
}
