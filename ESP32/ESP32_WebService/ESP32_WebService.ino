   
#include <WiFi.h>
#include <WebServer.h>
  
const char* ssid = "FEXIBUS 2G";
const char* password =  "Spider1977";

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


WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

    Serial.print("Conectando na rede WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Rede WiFi conectada com sucesso! Seu IP -> ");
  Serial.print(WiFi.localIP());
  
  server.begin();

  
  
}



void loop() {
  
  WiFiClient client = server.available();

    client.println(index_html);  



}
