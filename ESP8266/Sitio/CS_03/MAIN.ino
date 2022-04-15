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

  router();

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

void setDoors(){
  for(int i=0; i<8; i++){       
    digitalWrite(outdoor[i], stat_val[i]);      
  }
}
