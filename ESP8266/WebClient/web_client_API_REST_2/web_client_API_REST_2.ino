#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"

HTTPClient http;

const char* cidade;
const char* date;
const char* tim;
//const double temp;
const char* desc;
        

void setup() {
  Serial.begin(115200);

  WiFi.begin("Tales", "naotemsenha");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());  

      http.begin("http://api.hgbrasil.com/weather?woeid=458878&key=f65a34f9");
      int httpCode = http.GET();

      if (httpCode > 0) {

        String payload = http.getString();
        Serial.println(payload);
//        Serial.println(payload.length());
        int len = payload.length()+1;
        StaticJsonDocument<1500> doc;

        char json[len];
        payload.toCharArray(json,len);              
        DeserializationError error = deserializeJson(doc, json);
        if (error) {
//          Serial.print(F("deserializeJson() failed: "));
//          Serial.println(error.f_str());
          return;
        }

        
        cidade = doc["results"]["city_name"];
        date = doc["results"]["date"];
        tim = doc["results"]["time"];
        const double temp = doc["results"]["temp"];
        desc = doc["results"]["description"];

        Serial.print("Cidade:");
        Serial.println(cidade);
        Serial.print("Data:");
        Serial.println(date);
        Serial.print("Hora:");
        Serial.println(tim);
        Serial.print("Temperatura:");
        Serial.println(temp);
        Serial.print("ALERTA:");
        Serial.println(desc);

      }

      http.end();



}

void loop() {

    if (WiFi.status() == WL_CONNECTED) {
//      Serial.println("Conected...");

 
 
    }
 
  delay(60000);    // 1min
  Serial.println(".");
}
