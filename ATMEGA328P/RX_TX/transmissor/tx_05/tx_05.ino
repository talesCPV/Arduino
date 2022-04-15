// Transmitter code for ESP8266 LoRa
#include <ESP8266WiFi.h>
#include <DNSServer.h>                  // Patched lib
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "EBYTE.h"

#define PIN_M0 4
#define PIN_M1 5
#define PIN_AX 6

float ii = 0.0;

SoftwareSerial ESerial(20, 19); // RX TX

void setup() {
  ESerial.begin(9600);
  Serial.begin(9600);
  Serial.print("Receptor");

}

void loop() {
  ESerial.println("Teste, 123...");
  Serial.println("Teste, 123...");
  delay(200);  
}
