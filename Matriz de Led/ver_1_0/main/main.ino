// Inclusão de Bibliotecas
#include <LedControl.h>
#include <Wire.h>

// Variáveis de configuração da Matriz de Led
int DIN = 10;
int CS =  9;
int CLK = 8;
LedControl matrizLed = LedControl(DIN, CLK, CS, 4);




 
