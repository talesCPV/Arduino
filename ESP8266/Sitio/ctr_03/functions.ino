void setup() {

    for(int i=0; i<8; i++){
      pinMode(luz[i], OUTPUT);    
    }

  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, pass);

  dnsServer.start(DNS_PORT, "*", apIP);  

  turn(ler(0));

  server.onNotFound([]() {
    const String call = server.arg("hdn_call");
    String dt_byte = server.arg("hdn_data");
    byte mydata = getValue(dt_byte);
    server.send(200, "text/html", indexHTML);
       
     if(call == "LUZ"){  
        gravar(0,mydata); 
        turn(ler(0));
     }
  
  });

  server.on("/luz", HTTP_GET, [](){
      server.send(200, "text/plain", String(ler(0)).c_str());
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

void turn(byte dt){
  for(int i=0; i<8; i++){
      bitRead(dt,i) ? digitalWrite(luz[i], HIGH) : digitalWrite(luz[i], LOW);
  }  
}

byte getValue(String N){
  Serial.println(N);
  byte out = B00000000;

  for(int i=0; i<8; i++){
    if(N[i]== 49){ // 49 = ASCII "1"
        bitWrite(out, i, 1);
    }    
  }
  return out;
}


int gravar(int endereco, byte valor){
  Serial.println("gravando...");
  EEPROM.begin(4096);
  EEPROM.write(endereco, valor);  
  EEPROM.end();
}

byte ler(int endereco){
  Serial.println("lendo dados...");
  EEPROM.begin(4096);  
  int resp = EEPROM.read(endereco);
  EEPROM.end();
  return (byte)resp;
}
