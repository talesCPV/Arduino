
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

  StaticJsonDocument<1400> doc;
  json = readfile("/config.json");

   // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  
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

/*
void savedevice(){
  String device = server.arg("ip");
  device += server.arg("mac");
  device += server.arg("name");
  createfile("/device.db", device) : 0;
  refreshData();
  setDoors();
}
*/
String getClientData(String url){

  WiFiClient client;

  int    HTTP_PORT   = 81;
  String HTTP_METHOD = "GET"; // or "POST"
  //char   HOST_NAME[] = url; // hostname of web server:
  String PATH_NAME   = "";  
  
  if(client.connect(url, 81)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("connection failed");
  }
  
}


String dumpDevices(){
  IPAddress  address;
  unsigned char number_client;
  struct station_info *stat_info;
  struct ip4_addr *IPaddress;
  //clear menuItens
  for(int i=0; i<15; i++){
    menuitem[i] = 0;
  }

  String devices = "";
  number_client= wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();  
  devices = number_client;
  devices += "\r\n";
  devices += apIP.toString() +"|"+ WiFi.macAddress();
  
  devices += apIP.toString() +"|"+ WiFi.macAddress();
  devices += "\r\n";

  while (stat_info != NULL){
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;
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

void setup() {

//*((volatile uint32_t*) 0x60000900) &= ~(1); // Hardware WDT OFF

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

  server.on("/devices", HTTP_GET, [](){
    server.send(200, "text/plain", dumpDevices());
  });

  server.on("/savedevices", HTTP_GET, [](){
    server.send(200, "text/plain", dumpDevices());
  });

  server.on("/teste", HTTP_GET, [](){
    getClientData("10.10.10.101/savedata");
    server.send(200, "text/plain", dumpDevices());
  });

  
  server.begin();
  setDoors();
}

void loop() {
  
  if(root || stat_server){
    dnsServer.processNextRequest();
  }
 
  server.handleClient();

  if(digitalRead(BTN_CONF)){
    Serial.print("click... Connected, IP address: ");
    Serial.println(WiFi.localIP());
    delay(100);
  }

}

String parseJson(String json, String field){

  const char* value = "";

  StaticJsonDocument<1500> doc;
  DeserializationError error = deserializeJson(doc, json);
  
  if (!error) {
    value = doc[field];
  }
  return value;
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
