
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>

const char* ssid     = "Display_led";
const char* password = "123456";

String texto = "";
const char* PARAM = "input1";

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object

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

  texto = ler(0);
  
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
