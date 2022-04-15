/******** INCLUDE ********//*
 PROGRAMED BY: Tales Cembraneli Dantas
 Date: 10/04/2022
 Version: 2.0
 
/******** INCLUDE ********/
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <FS.h>
#include <ArduinoJson.h>

/******** DEFINES ********/
#define BTN_CONF 10
#define LED 2
#define DNS_PORT 53

/******* VARIABLES *******/
String ssid;
String pass;
boolean root = false;
boolean stat_server = false;
byte mydoors = B00000000;
int outdoor[8] = {16,5,4,0,14,12,13,15};
String json;

/******* INSTANCES *******/
ESP8266WebServer  server(80);
IPAddress         apIP(10,10,10,1);
DNSServer         dnsServer;

void setup() {

/********  START CPU  ********/  

  Serial.begin(115200);
  Serial.println();
  delay(200);

  pinMode(BTN_CONF, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  for(int i=0; i< 7; i++){
    pinMode(outdoor[i], OUTPUT);    
  }
  
/*******    FILE SYSTEM   ********/

  if (!SPIFFS.begin()) {
    Serial.println("Error mounting the file system");
    return;
  }
  refresh();
  delay(200);
  
/****** PUT IN ROOT MODE ******/

  if(readBit(0,0)){
    digitalWrite(LED,HIGH);
    root = true;
    pass = "12345678";
    ssid = "ROOT_MODE";
    digitalWrite(LED,HIGH);
    writeBit(0,0,0);
  }else{
    root = false;
    ssid = jsonStr(json,"ssid");
    pass = jsonStr(json,"pass");
    digitalWrite(LED,LOW);
    stat_server = readBit(0,1) ? true : false;
  }

/*** CONNECTING NETWORK ***/

  login();  
}

void loop() {
  
   if(root){
      dnsServer.processNextRequest();
    }else{
      if(!digitalRead(BTN_CONF)){
        root_reset();
      }      
    }

  server.handleClient();
}
