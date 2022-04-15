#include <LedControl.h>
#include <Wire.h>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

#include <EEPROM.h>

#define DIN 13
#define CS 2
#define CLK 14
#define SCROLL_SPEED 100 // miliseconds

byte disp[5][8];
byte* ascii[91];
int cont[2] = {0,0}; 

const char* ssid     = "Display_led";
const char* password = "123456";

String texto = ""; // frase
const char* PARAM = "input1";

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object

LedControl matrizLed = LedControl(DIN, CLK, CS, 4);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;    // will store last time DHT was updated

// Updates DHT readings every 10 seconds
const long interval = 10000;  

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
  <title> Welcome NODE MCU </title>
</head>
<body>
  <h2>BACKGROUND</h2>

  <p>
    <span id="lblTexto"></span><br><br>

    <input type="text" id="edtTexto"/>
    <button id="btnSave"> Salvar </button>
  </p>

  <form action="/">
    input1: <input type="text" name="input1">
    <input type="submit" value="Submit">
  </form><br>
  
</body>
<script>

 const btnSave = document.getElementById("btnSave");
 const edtTexto = document.getElementById("edtTexto");
 const lblTexto = document.getElementById("lblTexto");

 btnSave.addEventListener("click",()=>{
   alert(edtTexto.value);
 });

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      lblTexto.innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/texto", true);
  xhttp.send();
}, 10000 ) ;


</script>
</html>)rawliteral";



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

byte inverte_byte(byte A){
  byte B;  
  int i;
  for(i=0; i<8; i++){
    bitWrite(B, i, bitRead(A, 7-i));
  }
  return B;
}
