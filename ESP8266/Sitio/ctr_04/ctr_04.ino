#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#define DNS_PORT 53

IPAddress         apIP(10, 10, 10, 1);
DNSServer         dnsServer;
ESP8266WebServer  server(80);

String ssid = "Ctr_Sitio";
String pass = "12345678";

int luz[8] = {16,5,15,0,2,14,12,13};
