#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>

#define DNS_PORT 53
#define BTN_CONF 10

IPAddress         apIP(10, 10, 10, 1);
DNSServer         dnsServer;
ESP8266WebServer  server(80);

const char* ssid;
const char* pass;
const char* stat_name;
boolean stat_server = true;
boolean stat_door[8];
boolean stat_val[8];
const char* door_name[8];
const char* menuitem[15];
String json;  
boolean root = false;
int outdoor[8] = {16,5,15,0,9,14,12,13};
