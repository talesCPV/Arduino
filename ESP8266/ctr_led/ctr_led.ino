#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#define led 5
#define DNS_PORT 53

IPAddress         apIP(10, 10, 10, 1);
DNSServer         dnsServer;
ESP8266WebServer  server(80);

String ssid = "Controla_led";
String pass = "12345678";
