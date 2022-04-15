void setup() {
  
  Serial.begin(115200);
//  gravar(0x21,"Tales C. Dantas");
//  gravar(0x02,"Matriz de Led");
//  gravar(0x11,"12345678");
//  gravar_valor(0x00,0x00); // grava 0 no BLANK 0
//  gravar_valor(1,10); // grava 10 no SCROLL_SPEED (x 10) = 100ms

  frase = ler(0x21);
  ssid = ler(0x02);
  pass = ler(0x11);
  ascii_begin();
  display_begin();

  BLANK = ler_valor(0);
  SCROLL_SPEED = ler_valor(1) * 10; // SCROLL_SPEED = valor memoria 1 x 10 (milisegundos)

  Serial.print("SCROLL_SPEED -> ");
  Serial.println(SCROLL_SPEED);

  // configure access point
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, pass);

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  loadHTML();

  roterHTML();
  
  server.begin();
}

void loop() {
  
  dnsServer.processNextRequest();
  server.handleClient();
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= SCROLL_SPEED) {
    
    previousMillis = currentMillis;
    cont[0]++;
    if(cont[0] == 8){
      cont[0] = 0;
      if(cont[1] < frase.length()){
        getLetter(int(frase[cont[1]]));
        cont[1]++;
        
      }else{
        cont[1]++;
        getLetter(0x20);// adiciona BLANK SPACES no final
        if(cont[1] >= frase.length()+BLANK){
          cont[1] = 0;
          Serial.print("frase atual -> ");
          Serial.println(frase);          
        }

      }
    }  
    show_text();
    scroll();
    
  }

}

void display_begin(){
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
}

void gravar(int endereco,String dados){
  
  int tam = dados.length();
  EEPROM.begin(endereco+tam+1);

  for(int i=0; i < tam; i++){
     EEPROM.write(endereco+i, dados[i]);    
  }

  EEPROM.write(endereco+tam, 0xff);
  EEPROM.commit();//Salva o dado na EEPROM.  
  EEPROM.end();  

  Serial.println("Dado salvo na EEPROM.");
  
}

int gravar_valor(int endereco, byte valor){
  EEPROM.begin(4096);
  EEPROM.write(endereco, valor);  
//  EEPROM.write(endereco+1, 0xff);
  EEPROM.end();
}

String ler(int endereco){
  String resp = "";
  Serial.println("******INICIA LEITURA******");
  EEPROM.begin(4096);  
  int i = endereco;
  int ascii = EEPROM.read(i);
  
  while(ascii < 0xff){
    resp += char(ascii);
    i++;
    ascii = EEPROM.read(i);    
  }
     
  EEPROM.end();
  return resp;
}

int ler_valor(int endereco){
  EEPROM.begin(4096);  
  int resp = EEPROM.read(endereco);
  EEPROM.end();
  return resp;
}

void getLetter(int ASC){
  int i;
  ASC -= 32;
  for(i=0; i<8; i++){
    if(ASC >=0 && ASC <=90){
      disp[4][i] = ascii[ASC][i];
    }else{
      disp[4][i] = ascii[0][i];      
    }
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

byte inverte_byte(byte A){
  byte B;  
  int i;
  for(i=0; i<8; i++){
    bitWrite(B, i, bitRead(A, 7-i));
  }
  return B;
}

void loadHTML(){
  
    SPIFFS.begin();
  
    File file = SPIFFS.open("/index.html", "r");
    html = file.readStringUntil('\r');
    file.close();
  
    file = SPIFFS.open("/style.css", "r");
    css = file.readStringUntil('\r');
    file.close();
  
    file = SPIFFS.open("/functions.js", "r");
    js = file.readStringUntil('\r');
    file.close();

  SPIFFS.end();
}

void roterHTML(){

  // replay to all requests with same HTML
  server.onNotFound([]() {
    const char* FRASE = "edtFrase";
    const char* VELOCIDADE = "cmbVel";
    const char* ESPACO = "cmbEsp";
    const char* GSSID = "edtSSID";
    const char* PASS = "edtNewPass";

    server.send(200, "text/html", String(html).c_str());
    String value = server.arg(FRASE);
    if(value != ""){
      Serial.print("GRAVANDO NA EEPROM -> ");
      Serial.println(value);
      gravar(0x21,value);
      frase = value;
      cont[0] = 0;
      cont[1] = value.length(); // coloca o cont 1 no inicio do BLANK spaces
    }
    value = server.arg(VELOCIDADE);
    if(value != ""){
      Serial.print("VELOCIDADE DO SCROLL -> ");
      Serial.println(value);
      gravar_valor(0x01,value.toInt());
      SCROLL_SPEED = value.toInt() * 10;
    }

    value = server.arg(ESPACO);
    if(value != ""){
      Serial.print("ESPAÇOS -> ");
      Serial.println(value);
      gravar_valor(0x00,value.toInt());
      BLANK = value.toInt();
    }

    value = server.arg(GSSID);
    if(value != ""){
      Serial.print("SSID -> ");
      Serial.println(value);
      gravar(0x02,value);
    }    

    value = server.arg(PASS);
    if(value != ""){
      Serial.print("PASS -> ");
      Serial.println(value);
      gravar(0x11,value);
    }    
  });
  
/*  
  server.on("/", [](){
    server.send(200, "text/html", String(html).c_str());
  });
*/
  server.on("/style.css", [](){
    server.send(200, "text/css", String(css).c_str());
  });

  server.on("/functions.js", [](){
    server.send(200, "text/html",String(js).c_str());
  });

  server.on("/frase", HTTP_GET, [](){
    server.send(200, "text/plain", String(frase).c_str());
  });
    
}
