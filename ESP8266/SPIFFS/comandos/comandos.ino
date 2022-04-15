#include <FS.h>

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Begin...");

  listaArq();
  
//  formatFiles();

  lerBitaBit("/teste.txt");
  
  lerTexto("/sketch.js");

//  novoArq("/arq1.txt","teste");

//  renameArq("/arq2.txt","/arq3.txt");

//  delArq("/arq3.txt");

  Serial.println("End...");

}

void loop() {


}

void lerBitaBit(String path){
  SPIFFS.begin();
  
  File file = SPIFFS.open(path, "r");
  while (file.available()){
    Serial.println(file.read()); 
  }
  file.close();
  
  SPIFFS.end();
}

void lerTexto(String path){
  SPIFFS.begin();
  
  File file = SPIFFS.open(path, "r");
  Serial.println(file.readStringUntil('\r')); 
  file.close();
  
  SPIFFS.end();
}



void novoArq(String path, String texto){
  SPIFFS.begin();
  
  File file = SPIFFS.open(path, "w");
  file.print(texto);
  file.close();
  
  SPIFFS.end();
}

void delArq(String path){
  SPIFFS.begin();  
  
  if(SPIFFS.exists(path)){
    SPIFFS.remove(path);
  }

  SPIFFS.end();
  
}

void renameArq(String oldOne, String newOne){
  SPIFFS.begin();

  if(SPIFFS.exists(oldOne)){
    SPIFFS.rename(oldOne, newOne);
  }
  
  SPIFFS.end();
}

void listaArq(){
  SPIFFS.begin();
  
  String str = "Files:\r\n";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str += dir.fileName();
      str += " / ";
      str += dir.fileSize();
      str += "\r\n";
  }
  Serial.println(str);
  
  SPIFFS.end(); 
}

void formatFiles(){
  SPIFFS.begin();
  SPIFFS.format();
  SPIFFS.end(); 
}
