#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SPEED 400

//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,20,4);

String screen[4] = {"","","",""};
int count[4] = {0,0,0,0};

 
void setup()
{
  lcd.init();
  lcd.setBacklight(HIGH);

  Serial.begin(9600);

  screen[1] = "Tales";
  screen[2] = "segunda linha do display de 20x4";
  screen[3] = "cara, vamos ficar aqui enchendo linguica pq nao tenho mais oq escrever";

}
 
void loop()
{
  show();
}

void show(){

  for(int y=0; y<4; y++){
    int row_size = screen[y].length();
    for(int x=0; x<20; x++){
        lcd.setCursor(x,y);
        if(x < row_size){
          lcd.print(screen[y][count[y] + x]);        
        }
    }
    if(count[y] < (row_size - 20)) {
       count[y]++; 
    }else{
      count[y] = 0;
    }

  }
  delay(SPEED);
}
