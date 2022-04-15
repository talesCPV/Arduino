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

  Serial.begin(9600);   // Serial para debug, se necessário

  delay(100);

}

int index=0;
String frase = "GAME OVER!";
int show[4];

void loop() {

  fill_display();
  delay(500);
  
  index++;
  if(index == frase.length()-3){
    delay(1000);
    index = 0;
  }

}

void fill_display(){
  int pointer[4];
  
  pointer[0] = int(frase[index]);
  pointer[1] = int(frase[index+1]);
  pointer[2] = int(frase[index+2]);
  pointer[3] = int(frase[index+3]);
  
  imprimeBloco(0, ascii[pointer[0]]);
  imprimeBloco(1, ascii[pointer[1]]);
  imprimeBloco(2, ascii[pointer[2]]);
  imprimeBloco(3, ascii[pointer[3]]);
}

byte inverte_byte(byte A){
  byte B;  
  int i;
  for(i=0; i<8; i++){
    bitWrite(B, i, bitRead(A, 7-i));
  }
  return B;
}

// Função que faz a impressão direta nos pinos da Matriz de Led
void imprimeBloco(int lcd, byte character [])
{
  int i;
  for (i = 0; i < 8; i++)
  {
    matrizLed.setRow(lcd, 7-i, inverte_byte(character[i]));
  }
}
