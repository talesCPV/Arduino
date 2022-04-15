String parseJson(String json, String field){

  const char* value = "";

  StaticJsonDocument<1500> doc;
  DeserializationError error = deserializeJson(doc, json);
  
  if (!error) {
    value = doc[field];
  }
  return value;
}

void savedata(){
  const String file = server.arg("file");
  const String save = server.arg("save");
  const String json = server.arg("data");
  save == "true" ? createfile(file, json) : 0;
  refreshData();
  setDoors();
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
