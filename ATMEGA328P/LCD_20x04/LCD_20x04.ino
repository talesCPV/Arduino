// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin (20,4);
}
 
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("**** Menu ****");
  lcd.setCursor(0,1);
  lcd.print("-> Opcao 01");
  lcd.setCursor(0,2);
  lcd.print("   Opcao 02");
  lcd.setCursor(0,3);
  lcd.print("   Opcao 03");
  
  delay(1000);
//  lcd.setBacklight(LOW);
//  delay(1000);
}
