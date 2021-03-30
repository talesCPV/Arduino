#include <LedControl.h>
#include <Wire.h>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

#include <EEPROM.h>

#define DIN 13
#define CS 2
#define CLK 14
#define SCROLL_SPEED 100 // miliseconds

byte disp[5][8];
byte* ascii[91];
int cont[2] = {0,0}; 

const char* ssid     = "Display_led";
const char* password = "123456";

String texto = ""; // frase
const char* PARAM = "input1";

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object

LedControl matrizLed = LedControl(DIN, CLK, CS, 4);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;    // will store last time DHT was updated

// Updates DHT readings every 10 seconds
const long interval = 10000;  

byte inverte_byte(byte A){
  byte B;  
  int i;
  for(i=0; i<8; i++){
    bitWrite(B, i, bitRead(A, 7-i));
  }
  return B;
}
