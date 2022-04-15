void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  digitalWrite(led, HIGH);
  // configure access point
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, pass);

  dnsServer.start(DNS_PORT, "*", apIP);  

  server.onNotFound([]() {
    const char* LED = "hdnLED";

    server.send(200, "text/html", indexHTML);
    String value = server.arg(LED);
     if(value == "1"){
        digitalWrite(led, HIGH);
     }else{
        digitalWrite(led, LOW);   
     }

  
  });

  server.on("/led", HTTP_GET, [](){
    if(digitalRead(led)){
      server.send(200, "text/plain", String("1").c_str());
    }else{
      server.send(200, "text/plain", String("0").c_str());
    }
  });

  server.begin();
  
  

}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
