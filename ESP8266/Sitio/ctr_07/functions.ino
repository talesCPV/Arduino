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
    const String save = server.arg("hdn_save");
    const String dt_byte = server.arg("hdn_data");
        
    byte mydata = getValue(dt_byte);
    server.send(200, "text/html", indexHTML);
     Serial.write(200);
          
     if(call == "LUZ"){  
        save == "1" ? gravar(0,mydata): 0;              
        turn(mydata);
     }
  
  });

  server.on("/luz", HTTP_GET, [](){
      server.send(200, "text/plain", String(ler(0)).c_str());
  });

  server.on("/config", HTTP_GET, [](){
      server.send(200, "text/plain", dumpDevices().c_str());
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

String dumpDevices(){
  String devices = "";
  number_client= wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();  
  devices = number_client;
  devices += "\r\n";
  devices += apIP.toString() +"|"+ WiFi.macAddress();
  devices += "\r\n";

  while (stat_info != NULL){
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;
    devices += "\t";
    devices += address.toString();
    devices += "|";    
    devices += String(stat_info->bssid[0],HEX) + ":";
    devices += String(stat_info->bssid[1],HEX) + ":";
    devices += String(stat_info->bssid[2],HEX) + ":";
    devices += String(stat_info->bssid[3],HEX) + ":";
    devices += String(stat_info->bssid[4],HEX) + ":";
    devices += String(stat_info->bssid[5],HEX);
    devices += "\r\n";    
       
    stat_info = STAILQ_NEXT(stat_info, next);
  } 
  return devices;
}

char readfile(String path){
  char out;
  File file = SPIFFS.open(path, "r");
 
  if (!file) {
    Serial.println("Failed to open file for reading");    
  }
  
  while (file.available()) {
    out += file.read();
  }
 
  file.close();
  return out;
}

bool createfile(String path, String txt){
  
    File file = SPIFFS.open(path, "w");
 
    if (!file) {
      Serial.println("Error opening file for writing");
      return false;
    }
   
    int bytesWritten = file.print(txt);
    file.close();
    
    if (bytesWritten == 0) {
      Serial.println("File write failed");
      return false;
    }
      
    return true;
    
      
}
