#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WebServer server(80);
String html, css, js;

void setup() {
  Serial.begin(115200);

  SPIFFS.begin();
  
    File file = SPIFFS.open("/index.html", "r");
    html = file.readStringUntil('\r');
    file.close();
  
    file = SPIFFS.open("/style.css", "r");
    css = file.readStringUntil('\r');
    file.close();
  
    file = SPIFFS.open("/functions.js", "r");
    js = file.readStringUntil('\r');
    file.close();

  SPIFFS.end();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin("Tales", "naotemsenha");
  Serial.print("Conectando na rede WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Rede WiFi conectada com sucesso! Seu IP -> ");
  Serial.print(WiFi.localIP());

  

  server.on("/", [](){
    server.send(200, "text/html", String(html).c_str());
  });

  server.on("/style.css", [](){
    server.send(200, "text/css", String(css).c_str());
  });

  server.on("/functions.js", [](){
    server.send(200, "text/html",String(js).c_str());
  });

  server.begin();
  
}

void loop() {
  server.handleClient();
}
