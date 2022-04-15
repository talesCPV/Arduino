
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

void refreshData(){

  refreshJSON();
  delay(100);
  stat_name = doc["name"];
  stat_server = doc["server"];
  ssid = doc["ssid"]; 
  pass = doc["pass"];
  
  for(int i=0; i<8; i++){
    door_name[i] = doc["door_name"][i];     
    stat_door[i] = doc["door_enable"][i];
    stat_val[i] = doc["door_value"][i]; 
  }
} 

void refreshJSON(){
  
  json = readfile("/config.json");

   // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  
}

void setDoors(){
  for(int i=0; i<8; i++){       
    digitalWrite(outdoor[i], stat_val[i]);      
  }
}

void savedata(){
  const String file = server.arg("file");
  const String save = server.arg("save");
  const String json = server.arg("data");
  save == "true" ? createfile(file, json) : 0;
  refreshData();
  setDoors();
}

void setup() {

/******  START CPU  ******/  
  Serial.begin(115200);
  delay(200);

  pinMode(BTN_CONF, INPUT);
  pinMode(LED_BUILTIN,OUTPUT);

  for(int i=0; i<8; i++){
    pinMode(outdoor[i], OUTPUT);    
  }

  /*******    FILE SYSTEM   ********/

  if (!SPIFFS.begin()) {
    Serial.println("Error mounting the file system");
    return;
  }
  delay(200);
  refreshData();
        
  Serial.print("SSID:");
  Serial.println(ssid);
  
/******  CONECTING NETWORK  ******/ 

  if(digitalRead(BTN_CONF)){
    root = true;
    pass = "12345678";
    ssid = "ROOT_MODE";
    ap_station();
  }else{   
    if(stat_server) {      
      ap_station();
    }else{
      wc_station();
    }
  }

  
 /******  TESTES  ******/

//  gravar(1,B00000011);
//  deletefile("/teste.txt");
//  deletefile("/index.html");
//  Serial.println(listfile("/"));

  setDoors();
  /********************************/


  
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

  server.begin();
  
}

void loop() {
  dnsServer.processNextRequest();  
  server.handleClient();

  if(digitalRead(BTN_CONF)){
    Serial.println("click...");
  }

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

String readfile(String path){
  
  File file = SPIFFS.open(path, "r");
 
  if (!file) {
    Serial.println("Failed to open file for reading");
  }

  String out= "";
  
  while (file.available()) {
    out += (char)file.read();   
  }

  file.close();
  return out;
}

String listfile(String path){
  String out = "";
  Dir dir = SPIFFS.openDir(path);
  while (dir.next()) {
      out += dir.fileName();
      out += " size-> ";
      out += dir.fileSize();
      out += "\r\n";
  }
  return out;
}

bool deletefile(String path){
  
  if(SPIFFS.exists(path)){
    SPIFFS.remove(path);
    return true; 
  }else{
    return false;
  }  
  
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
    }else{
      return true;
    }
      
}
