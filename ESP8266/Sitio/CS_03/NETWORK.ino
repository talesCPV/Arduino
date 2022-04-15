void router(){
    
  server.onNotFound([]() {         

      if(root){
        Serial.println("modo root");        
        server.send(200, "text/html",rootHTML);       
      }else{
        if(stat_server){
          // SERVER
          server.send(200, "text/html", indexHTML);
        }else{
          // CLIENT
          server.send(200, "text/html", clientHTML);
          
        }        
      }
      savedata();
     Serial.write(200);
  });

  server.on("/savedata", HTTP_GET, [](){
    server.send(200, "text/plain", json);
  });

  server.on("/devices", HTTP_GET, [](){
    server.send(200, "text/plain", dumpDevices());
  });

  server.on("/savedevices", HTTP_GET, [](){
    server.send(200, "text/plain", dumpDevices());
  });

  server.on("/teste", HTTP_GET, [](){
 
    server.send(200, "text/plain", dumpDevices());
  });
  
  server.begin();
}


void ap_station(){ // access point

    Serial.println("Acces point...");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, pass);
    dnsServer.start(DNS_PORT, "*", apIP);  
      
}

void wc_station(){ // web client

  int count = 0;
  Serial.println("Web Client...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
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
