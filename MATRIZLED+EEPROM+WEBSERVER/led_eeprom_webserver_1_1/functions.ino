void setup(){
   
  // Serial port for debugging purposes
  Serial.begin(115200);
  ascii_begin();
  
  texto = ler(0);

  // Configura e inicializa cada bloco de Led da Matriz
  matrizLed.shutdown(0, false);
  matrizLed.setIntensity(0, 1);
  matrizLed.clearDisplay(0);

  matrizLed.shutdown(1, false);
  matrizLed.setIntensity(1, 1);
  matrizLed.clearDisplay(1);

  matrizLed.shutdown(2, false);
  matrizLed.setIntensity(2, 1);
  matrizLed.clearDisplay(2);

  matrizLed.shutdown(3, false);
  matrizLed.setIntensity(3, 1);
  matrizLed.clearDisplay(3);

  delay(100);


  
  Serial.print("Setting AP (Access Point)…");

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  dnsServer.start(DNS_PORT, "*", apIP);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){

    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM)) {
      inputMessage = request->getParam(PARAM)->value();
      inputParam = PARAM;
      gravar(0,inputMessage);
      texto = ler(0);
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);

    
    request->send_P(200, "text/html", index_html);
  });
  
  server.on("/texto", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(texto).c_str());
  });

//  readParans();

  // Start server
  server.begin();
}

void loop(){
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    Serial.print("Texto da EEPROM: ");
    Serial.println(texto);
    
  }

  cont[0]++;
  if(cont[0] == 8){
    cont[0] = 0;
    getLetter(int(texto[cont[1]]));
    cont[1]++;
    if(cont[1] == texto.length()){
      cont[1] = 0;
    }
  }  
  show_text();
  scroll();

  delay(SCROLL_SPEED);
}

void gravar(int endereco, String dados){
  
  int tam = dados.length();
  EEPROM.begin(endereco+tam+1);

  for(int i=0; i<tam; i++){
   EEPROM.write(endereco+i, dados[i]);    
  }
  EEPROM.write(endereco+tam, 0xff);    
  EEPROM.commit();//Salva o dado na EEPROM.  
  EEPROM.end();  

  Serial.println("Dado salvo na EEPROM.");
  
}

String ler(int endereco){
  Serial.println("******INICIA LEITURA******");
  EEPROM.begin(4096);  
  int ascii=0;
  int tam = 0;
  int i = endereco;
  while(ascii != 0xff){
    ascii = EEPROM.read(i);
    i++;
    if(ascii != 0xff){
      char letter = ascii;
      tam++;      
      Serial.print(ascii);  
      Serial.print(" - ");  
      Serial.println(letter);  
    }
  }
  Serial.print("Tamanho da string: ");  
  Serial.println(tam);
  char frase[tam];
  for(int i=0; i<tam; i++){
    frase[i] = EEPROM.read(i);
  }
       
  EEPROM.end();
  return frase;
}

void getLetter(int ASC){
  int i;
  for(i=0; i<8; i++){
    disp[4][i] = ascii[ASC-32][i];
  }  
}

void scroll(){
  int i;
  for(i=0; i<5; i++){
      scroll_block(i);
  }
}

void scroll_block(int block){
  int i;
  for(i=0; i<8; i++){
      disp[block][i] = disp[block][i] << 1;
      if(block < 4){
        bitWrite(disp[block][i], 0, bitRead(disp[block+1][i], 7));
      }else{
        bitWrite(disp[block][i], 0, 0);
      }
  }
}

void show_text(){
    int i;
  for(i=0; i<4; i++){
    imprimeBloco(i, disp[i]);  
  }
}

void imprimeBloco(int lcd, byte character [])
{
  int i;
  for (i = 0; i < 8; i++)
  {
    matrizLed.setRow(lcd, 7-i, inverte_byte(character[i]));
  }
}
