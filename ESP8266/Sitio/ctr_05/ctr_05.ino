#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <EEPROM.h>

#define DNS_PORT 53

IPAddress         apIP(10, 10, 10, 1);
DNSServer         dnsServer;
ESP8266WebServer  server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

String ssid = "Ctr_Sitio";
String pass = "12345678";

int luz[8] = {16,5,15,0,2,14,12,13};

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    String dados = "00000000";
    Serial.write("TESTE=>");
    
    if(payload[0] == 'L'){  
          
      for(int i = 2; i < length; i++){
        dados[i-2] = payload[i];
      }
      Serial.println(dados);      
      turn(getValue(dados));
      
    }
   
    payload[1] == '1' ? gravar(0,getValue(dados)): 0;
        
  }
  
}
