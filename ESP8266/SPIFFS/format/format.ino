#include <FS.h>

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Begin...");
  
  SPIFFS.begin();
  Serial.println("SPIFFS begin...");
  
  String str = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str += dir.fileName();
      str += " / ";
      str += dir.fileSize();
      str += "\r\n";
  }
  Serial.println(str);

  Serial.println("end... 1");

  SPIFFS.format();

  str = "";
  dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str += dir.fileName();
      str += " / ";
      str += dir.fileSize();
      str += "\r\n";
  }
  Serial.print(str);

  Serial.println("end... 2");
}

void loop() {
  // put your main code here, to run repeatedly:

}
