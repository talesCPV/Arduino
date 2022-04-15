#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#define luz00 16
#define luz01 5
#define luz02 0
#define luz03 4
#define luz04 2
#define luz05 14
#define luz06 12
#define luz07 13



#define DNS_PORT 53

IPAddress         apIP(10, 10, 10, 1);
DNSServer         dnsServer;
ESP8266WebServer  server(80);

String ssid = "Ctr_Sitio";
String pass = "12345678";
