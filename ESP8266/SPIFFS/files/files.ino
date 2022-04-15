#include <FS.h>

String page;

void setup() {
  Serial.begin(115200);
  if(SPIFFS.begin()){

//  SPIFFS.format();
    
    File file = SPIFFS.open("/index.html", "r");

    if (!file) {
        Serial.println("Failed to open file for reading");
    }else{
      Serial.println();
/*
      while (file.available()) {   
        page += char(file.read());
        Serial.println(page);
      }
*/
        page = file.readStringUntil('\r');
        Serial.println(page);

      
      file.close();    
    }

    
  }else{
    Serial.println("error");
  }


  String str = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str += dir.fileName();
      str += " / ";
      str += dir.fileSize();
      str += "\r\n";
  }
  Serial.print(str);

 
  Serial.println("fim");

}

void loop() {

}
