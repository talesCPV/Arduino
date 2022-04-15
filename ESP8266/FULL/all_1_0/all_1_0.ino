/* A IDÉIA É CRIAR UM AP COM DNS 
 * NESTA WEBSERVER MONTA UMA PÁGINA
 * ONDE VC VERÁ TODAS AS REDES DISPONIVEIS
 * PODERÁ SELECIONAR UMA E SALVAR A SENHA
 * SALVA ESSES DADOS NA MEMORIA EEPROM
 * AO MESMO TEMPO TEMOS UM CLIENT MODE QUE
 * FICA TENTANDO SE CONECTAR A INTERNET
 * PELOS DADOS SALVOS NA EEPROM DE SSID E PASSWORD
 */


#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server
const byte        DNS_PORT = 53;          // Capture DNS requests on port 53

String responseHTML = "<!DOCTYPE html>"
  "<html lang=\"en\">"
  "<head>"
    "<meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<title>DNS</title>"
  "</head>"
  "<body>"
  "<p>Este é só um exemplo de DNS no 8266.</p>"
  "<button> ALERT!!! </button>"
  "</body>"
  "</html>";

String SSID_NET;
String PASS_NET;
String SSID_AP;
String PASS_AP;
String networks = "";


void setup() {
  Serial.begin(115200);

  SSID_AP = ler(0x02);  
  PASS_AP = ler(0x11);

  
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  delay(100);

  int n = WiFi.scanNetworks();
  
  for (int i = 0; i < n; i++)
  {
    networks += WiFi.SSID(i)+"|";
  }
  
  Serial.println(networks);

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_AP,PASS_AP);
  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();

//  gravar_valor(0x00,0x21);
//  gravar_valor(0x01,0xFE);

  
  Serial.println(ler_valor(0x00));
  Serial.println(ler_valor(0x01));
  Serial.println(ler(0x02));
  Serial.println(ler(0x11));
  Serial.println(ler(0x21));
  

}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();

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
  EEPROM.end();
}

String ler(int endereco){
  String resp = "";
  EEPROM.begin(4096);  
  int i = endereco;
  byte ascii = EEPROM.read(i);
  
  while(ascii < 0xff){
    resp += char(ascii);
    i++;
    ascii = EEPROM.read(i);    
  }
     
  EEPROM.end();
  return resp;
}

byte ler_valor(int endereco){
  EEPROM.begin(4096);  
  byte resp = EEPROM.read(endereco);
  EEPROM.end();
  return resp;
}
