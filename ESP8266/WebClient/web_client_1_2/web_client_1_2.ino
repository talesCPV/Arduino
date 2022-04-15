#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>
#include <ESP8266WebServer.h>
#include <FS.h>

String json; 

HTTPClient http;
ESP8266WebServer  server(80);

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin()) {
    Serial.println("Error mounting the file system");
    return;
  }
  
  json = readfile("/config.json");
  Serial.println(json);


  WiFi.begin("rede_teste", "12345678");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());  

  server.onNotFound([]() {               
    server.send(200, "text/plain","teste");       
//    Serial.write(200);
  });

  server.on("/savedata", HTTP_GET, [](){
    server.send(200, "text/plain", json);
  });

  server.on("/ssid", HTTP_GET, [](){
    server.send(200, "text/plain", readJson("ssid"));
  });

  server.begin();

}

void loop() {
    
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();
  }
 
}

String readfile(String path){
  
  File file = SPIFFS.open(path, "r");
 
  if (!file) {
    Serial.println("Failed to open file for reading");
  }

  String out= "";
  
  while (file.available()) {
    out += (char)file.read();   
  }

  file.close();
  return out;
}

String readJson(String field){

  const char* aux = "";

  StaticJsonDocument<1500> doc;
  DeserializationError error = deserializeJson(doc, json);
  
  if (!error) {
    aux = doc[field];
  }
  return aux;
}
