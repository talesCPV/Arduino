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
  act == "save" ? createfile(fl, dt) : 0;
  refresh(); 
  turn();
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
