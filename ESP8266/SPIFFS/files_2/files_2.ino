#include <FS.h>

 
void setup() {
 
  Serial.begin(115200); 
  if (!SPIFFS.begin()) {
    Serial.println("Error mounting the file system");
    return;
  }

  Serial.println(listfile("/"));

//  Serial.println("lendo arquivos /index.html");
//  Serial.println(readfile("/index.html"));
  
/*   
 
  if(deletefile("/file2.txt")){
    Serial.println("Arquivo deletado");
  }else{
    Serial.println("Problema ao tentar deletar arquivo");
  }
/*
  if(createfile("/index.html","<html>So um teste</html>")){
    Serial.println("Arquivo criado com sucesso");
  }else{
    Serial.println("Problema ao tentar criar arquivo");
  }

 */
}
 
void loop() {

  String aux = readfile("/config.json");

  delay(3000);
  Serial.print(aux);
  Serial.println();
  delay(3000);
  Serial.println(listfile("/"));
}

String readfile(String path){
  
  File file = SPIFFS.open(path, "r");
 
  if (!file) {
    Serial.println("Failed to open file for reading");
  }

  String out= "";
  
  while (file.available()) {
    out += (char)file.read();   
  }

  file.close();
  return out;
}


String listfile(String path){
  
  String out = "";
  Dir dir = SPIFFS.openDir(path);
  while (dir.next()) {
      out += dir.fileName();
      out += " size-> ";
      out += dir.fileSize();
      out += "\r\n";
  }
  return out;
}

bool deletefile(String path){
  
  if(SPIFFS.exists(path)){
    SPIFFS.remove(path);
    return true; 
  }else{
    return false;
  }  
  
}

bool createfile(String path, String txt){
  
    File file = SPIFFS.open(path, "w");
 
    if (!file) {
      Serial.println("Error opening file for writing");
      return false;
    }
   
    int bytesWritten = file.print(txt);
    file.close();
    
    if (bytesWritten == 0) {
      Serial.println("File write failed");
      return false;
    }else{
      return true;
    }
      
}
