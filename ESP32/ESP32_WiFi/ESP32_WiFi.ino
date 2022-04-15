   
#include <WiFi.h>
  
const char* ssid = "FEXIBUS 2G";
const char* password =  "Spider1977";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

    Serial.print("Conectando na rede WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Rede WiFi conectada com sucesso! Seu IP -> ");
  Serial.print(WiFi.localIP());
}



void loop() {
  // put your main code here, to run repeatedly:

}
