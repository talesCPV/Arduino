/* WIFI FUNCTIONS */

void login(){

  if(root){
    Serial.print("ROOT MODE...");
    access_point();
    
  }else if(stat_server) { 
    Serial.println("ACCESS POINT...");
    access_point();
  }else{
    Serial.println("WEB CLIENT...");    
    web_client();
  }
  
  router();
}

void access_point(){ // access point    
    
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, pass);
    dnsServer.start(DNS_PORT, "*", apIP);  
      
}

void web_client(){ // web client

  int count = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    digitalWrite(LED, !digitalRead(LED));
    count++;
    if(count > 30){
      Serial.print("Não consigo logar na rede ");
      Serial.print(ssid);
      Serial.println(", ssid ou senha errados!");
      break;    
    }
  }
  digitalWrite(LED_BUILTIN,LOW);
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());   
}

void router(){
    
  server.onNotFound([]() {

      if(root){
        server.send(200, "text/html", rootHTML);
      }else if(stat_server){
        server.send(200, "text/html", indexHTML);
      }else{
        server.send(200, "text/html", clientHTML);
      }
          
      Serial.write(200);
    
  });

  server.on("/json", HTTP_GET, [](){
    server.send(200, "text/plain", json);
  });

  server.on("/ram", HTTP_GET, [](){
    server.send(200, "text/plain", readMem());
  });

  server.on("/savedata", [](){
    saveData();
    server.send(200, "text/plain", "OK");
  });

  server.on("/reset", [](){
    Serial.println("RESET...");
    delay(3000);
    ESP.restart();
    server.send(200, "text/plain", "reset");
  });
  
  server.begin();
}
