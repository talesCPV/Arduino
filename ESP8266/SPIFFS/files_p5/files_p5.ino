#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WebServer server(80);
String html, p5, js;

void setup() {
  Serial.begin(115200);
  Serial.println("inicio!!!");
  
  SPIFFS.begin();
  
    File file = SPIFFS.open("/index.html", "r");
    html = file.readStringUntil('\r');
    file.close();
    Serial.println(html);

    file = SPIFFS.open("/sketch.js", "r");
    js = file.readStringUntil('\r');
    file.close();
    Serial.println(js);

/*    
    file = SPIFFS.open("/p5.min.js", "r");
    Serial.println(file.readStringUntil('\r'));
//    p5 = file.readStringUntil('\r');
    file.close();
*/    

  
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

  server.on("/sketch.js", [](){
    server.send(200, "text/html", String(js).c_str());
  });
/*
  server.on("/p5.min.js", [](){
    SPIFFS.begin();    
      File file = SPIFFS.open("/p5.min.js", "r");
      server.send(200, "text/html", file.readStringUntil('\r') );
    
    SPIFFS.end();
  });
*/  
/*
  server.on("/p5.min.js", [](){
    server.send(200, "text/html", String(p5).c_str());
  });
*/

  server.begin();
  
}

void loop() {
  server.handleClient();
}
