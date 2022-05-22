/* GERAL FUNCTIONS */

void root_reset(){  
  root = true;
  digitalWrite(LED,HIGH);
  writeBit(0,0,1);
  delay(3000);
  ESP.restart();    
}

void turn(){
  byte enab = getValue(jsonStr(json,"door_enable"));
  byte doors = getValue(jsonStr(json,"door_value"));
  for(int i=0; i<8; i++){
    digitalWrite(outdoor[i],bitRead(doors, i));
  }
}

void refresh(){
  json = readfile("/config.json");
  turn();
}

String readMem(){  
  
  String out = "";
  for(int adr=0; adr<3; adr++){
    out += "B";
    byte bits = read_ram(adr);
    for(int i=0; i<8; i++){
      if(bitRead(bits, i)){
        out += "1";
      }else{
        out += "0"; 
      }      
    }
    out += "\r\n";
  }  
  return out;  
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

void saveData(){
  const String fl = server.arg("file");
  const String act = server.arg("act");
  const String dt = server.arg("data");
  const String org = server.arg("org");
  
  act == "save" ? createfile(fl, dt) : 0;
  refresh(); 
  turn();
  if(org == "root"){
    //SAVE RAM EEPROM
    rec_ram(0,getValue(jsonStr(json,"ram"))); 
    rec_ram(1,getValue(jsonStr(json,"door_enable")));
  }
}

String jsonStr(String json, String field){

  const char* value = "";

  StaticJsonDocument<1500> doc;
  DeserializationError error = deserializeJson(doc, json);
  
  if (!error) {
    value = doc[field];
  }
  return value;
}

int jsonInt(String json, String field){

  int value = 0;

  StaticJsonDocument<1500> doc;
  DeserializationError error = deserializeJson(doc, json);
  
  if (!error) {
    value = (int)doc[field];
  }
  return value;
}

String dumpDevices(){
  IPAddress  address;
  unsigned char number_client;
  struct station_info *stat_info;
  struct ip4_addr *IPaddress;
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
