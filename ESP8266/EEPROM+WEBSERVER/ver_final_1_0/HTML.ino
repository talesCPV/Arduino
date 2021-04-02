
const char indexHTML[] PROGMEM = R"rawliteral(
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
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    #title {
      border-radius: 25px;
      border: 2px solid #73AD21;
      padding: 20px;
      width: 200px;
      height: auto;
      margin : auto;
    }
    #container {
      border-radius: 25px;
      background: #73AD21;
      padding: 20px;
      width: 200px;
      height: auto;
      margin : 10px auto; 
    }
  </style>
  <title> Welcome NODE MCU </title>
</head>
<body>
  <div id='title'> Matriz de Led </div>
  <div id='container'>
  
    <form action="/">
      <!--<p><span id="lblTexto"></span><br></p> -->
      <label> Digite uma nova frase</label>
      <input type="text" name="edtFrase">
      <label> Velocidade do Scroll</label>
      <select name="cmbVel">
        <option value="5">50 ms</option>
        <option value="10">100 ms</option>
        <option value="20">200 ms</option>
        <option value="40">400 ms</option>
        <option value="50">500 ms</option>
        <option value="75">750 ms</option>
        <option value="100">1 seg</option>
      </select>  
      <label> Espaços entre Ciclos</label>
      <select name="cmbEsp">
        <option value="1">1</option>
        <option value="2">2</option>
        <option value="3">3</option>
        <option value="4">4</option>
        <option value="5">5</option>
        <option value="10">10</option>
      </select>        
      <input type="submit" value="Salvar">
    </form><br>

  </div>
  
</body>
<script>

// const btnSave = document.getElementById("btnSave");
// const edtTexto = document.getElementById("edtTexto");
 const lblTexto = document.getElementById("lblTexto");
/*
 btnSave.addEventListener("click",()=>{
   alert(edtTexto.value);
 });
*/
</script>
</html>)rawliteral";
