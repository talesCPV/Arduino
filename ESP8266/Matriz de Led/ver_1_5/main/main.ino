#include <LedControl.h>
#include <Wire.h>

#define DIN 7
#define CS 5
#define CLK 4
#define SCROLL_SPEED 50 // miliseconds

byte disp[5][8];
byte* ascii[91];

int index = 0;
int cont = 0;

String frase = "INSERT ONE COIN TO PLAY... ";

LedControl matrizLed = LedControl(DIN, CLK, CS, 4);
