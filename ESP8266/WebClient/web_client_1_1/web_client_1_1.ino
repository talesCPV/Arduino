//#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"
#include <string.h>

HTTPClient http;

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

}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    Hora();

  }
 
  delay(60000);    // 1min
  Serial.println(".");
}

char Hora(){

  String RESP = "Cidade:";

      HTTPClient http;

      http.begin("http://worldtimeapi.org/api/timezone/Etc/GMT+3");
      int httpCode = http.GET();
 
      if (httpCode > 0) {

        String payload = http.getString();
//        Serial.println(payload);

        int len = payload.length()+1;
        StaticJsonDocument<1500> doc;

        char json[len];
        payload.toCharArray(json,len);

        
        DeserializationError error = deserializeJson(doc, json);

        if (!error) {

  
          const char* ip = doc["client_ip"];
          const char* date = doc["datetime"];
          const int dia_sem = doc["day_of_week"];
          const int dia_ano = doc["day_of_year"];
          const int sem_ano = doc["week_number"];

       
          Serial.print("IP:");
          Serial.println(ip);
          Serial.print("Data:");
          Serial.println(date);
          Serial.print("Dia da Semana:");
          Serial.println(dia_sem);
          Serial.print("Dia do Ano:");
          Serial.println(dia_ano);
          Serial.print("Semana Numero:");
          Serial.println(sem_ano);

          
        }
        
        doc.clear();

        
      }else{
        Serial.println("site fora do ar!");
      }
 
      http.end();
  
}
