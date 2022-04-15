void setup() {
  pinMode(luz00, OUTPUT);
  pinMode(luz01, OUTPUT);
  pinMode(luz02, OUTPUT);
  pinMode(luz03, OUTPUT);
  pinMode(luz04, OUTPUT);
  pinMode(luz05, OUTPUT);
  pinMode(luz06, OUTPUT);
  pinMode(luz07, OUTPUT);
  
  Serial.begin(115200);
//  digitalWrite(luz00, LOW);
  // configure access point
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, pass);


  dnsServer.start(DNS_PORT, "*", apIP);  

  server.onNotFound([]() {
    const String call = server.arg("hdn_call");
    String dt_byte = server.arg("hdn_data");
    
    server.send(200, "text/html", indexHTML);
    
    Serial.println(call);
//    Serial.println(getValue(dt_byte));
    byte mydata = getValue(dt_byte);
    Serial.println(mydata);
    
     if(call == "LUZ"){    
        
        bitRead(mydata,0) ? digitalWrite(luz00, HIGH) : digitalWrite(luz00, LOW);
        bitRead(mydata,1) ? digitalWrite(luz01, HIGH) : digitalWrite(luz01, LOW);
        bitRead(mydata,2) ? digitalWrite(luz02, HIGH) : digitalWrite(luz02, LOW);
        bitRead(mydata,3) ? digitalWrite(luz03, HIGH) : digitalWrite(luz03, LOW);
        bitRead(mydata,4) ? digitalWrite(luz04, HIGH) : digitalWrite(luz04, LOW);
        bitRead(mydata,5) ? digitalWrite(luz05, HIGH) : digitalWrite(luz05, LOW);
        bitRead(mydata,6) ? digitalWrite(luz06, HIGH) : digitalWrite(luz06, LOW);
        bitRead(mydata,7) ? digitalWrite(luz07, HIGH) : digitalWrite(luz07, LOW);
      
     }
  
  });

  server.on("/luz", HTTP_GET, [](){
      server.send(200, "text/plain", String("luz").c_str());
  });

  server.on("/porta", HTTP_GET, [](){
      server.send(200, "text/plain", String("porta").c_str());
  });

  server.on("/bomba", HTTP_GET, [](){
      server.send(200, "text/plain", String("bomba").c_str());
  });

  server.begin();
  
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}

byte getValue(String N){
  byte out = B00000000;

  for(int i=0; i<8; i++){
    if(N[i]== 49){ // 49 = ASCII "1"
        bitWrite(out, i, 1);
    }    
  }

  return out;
}
