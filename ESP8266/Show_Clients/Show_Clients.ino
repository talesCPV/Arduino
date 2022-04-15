#include <ESP8266WiFi.h>
#include<user_interface.h>

IPAddress apIP(10, 10, 10, 1);
IPAddress address;

String ssid = "Servidor";
String pass = "12345678";

unsigned char number_client;
struct station_info *stat_info;
struct ip4_addr *IPaddress;

void setup() {
  Serial.begin(9600);
  
  // configure access point
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, pass);

}

void loop() {
  delay(3000);
  dumpClients();
}


void dumpClients(){

  number_client= wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();
  
  Serial.print(" Total connected_client are = ");
  Serial.println(number_client);

  while (stat_info != NULL)
  {
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;
    Serial.print("\t");
    Serial.print(address);
    Serial.print("\r\n");
    stat_info = STAILQ_NEXT(stat_info, next);
  } 
}
