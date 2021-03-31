#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer  server(80);
void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("rede_01","12345678");
  WiFi.begin("Tales", "naotemsenha");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");

  server.begin();
  delay(100);
  
  Serial.println(WiFi.localIP());  
  Serial.println(WiFi.softAPIP());  
  
}

void loop() {

}
