// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

//int sel = 0;
String texto[4] = {"**** Menu ****","linha 01","linha 02",""};
int sel = 1;

void setup()
{
 lcd.begin (20,4);
 pinMode(13, INPUT);
 pinMode(12, INPUT);
 pinMode(11, INPUT);
 pinMode(10, INPUT);
 lcd.setBacklight(HIGH);
}
 
void loop()
{

  if(digitalRead(13)){
    sel = sel +1;
    if(sel > 3 or texto[sel] == ""){
      sel = 1;
    }
    delay(300);
  }
/*  
  if(digitalRead(12)){
    sel = sel -1;
    if(sel == 0 or texto[sel] == ""){
      sel = 3;
    }
    delay(300);
  }
 */   
  lcd.setCursor(0,0);
  if(digitalRead(10)){
    texto[0] = "**** Click ****";
  }else{
    if(digitalRead(11)){
      texto[0] = "**** Back ****";
    }else{
      texto[0] = "**** Menu ****";
    }
  }
  tela();

  
//  lcd.setBacklight(LOW);
//  delay(1000);
}

void tela()
{
  for (int i=0; i<4; i++){
    lcd.setCursor(0,i);
    if (sel == i){
      lcd.print(">"+texto[i]);
    }else{
      lcd.print(" "+texto[i]);
    }
  }
  
}
