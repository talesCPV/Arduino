  #include <ESP8266WiFi.h>
  #include <DNSServer.h>                  // Patched lib
  #include <ESP8266WebServer.h>
  #include <EEPROM.h>
  #include <LedControl.h>
  #include <Wire.h>
  #include <FS.h>
  
  #define DIN 13
  #define CS 2
  #define CLK 14
  #define DNS_PORT 53
  
  //const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
  IPAddress         apIP(10, 10, 10, 1);    // Private network for server
  DNSServer         dnsServer;              // Create the DNS object
  ESP8266WebServer  server(80);          // HTTP server
  LedControl matrizLed = LedControl(DIN, CLK, CS, 4);

  int BLANK = 0;
  int SCROLL_SPEED = 0;
  int cont[2] = {0,0};

  //const long interval = 10000;
  unsigned long previousMillis = 0;
  
  byte disp[5][8];
  byte* ascii[91];
  
  String ssid = "Matriz_de_Led";
  String pass = "12345678";
  String frase = "";
  String networks;
  String html, css, js;
