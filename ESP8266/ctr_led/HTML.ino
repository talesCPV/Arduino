
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
  </style>
  <title> CTR LED </title>
</head>
<body>

    <div id="top" class="main">

        <div class="sub">
            <div class="head">
                <h1>  <a href="#main">Luz</a> </h1>
                <h1>  <a href="#leds">Portas</a> </h1>
                <h1>  <a href="#bomba">Bomba</a> </h1>
           
            </div>

            <p>Controle universal do Sítio</p>

        </div>
        <div id="main" class="sub">
            <div class="head">
                <h1>Luz</h1>
                <h1 class="up"> <a href="#top">↑</a> </h1> 
            </div>
        
        </div>
        <div id="leds" class="sub">
            <div class="head">
                <h1>Portas</h1>
                <h1 class="up"> <a href="#top">↑</a> </h1> 
            </div>

            <div class="content">

  <form>
    <input type="hidden" id="hdnLED" name="hdnLED" value="0">
    <button id="btnonoff">Send</button>
    <input type="checkbox" id="led01">
  </form>
            
                <div>
                    <input type="checkbox" name="ckb1">
                    <label for="ckb1">Led01</label>
                </div>
                <div>
                    <input type="checkbox" name="ckb2">
                    <label for="ckb2">Led02</label>
                </div>

                <button>Enviar</button>

            </div>


        </div>
        <div id="bomba" class="sub">
            <div class="head">
                <h1>Bomba</h1>
                <h1 class="up"> <a href="#top">↑</a> </h1> 
            </div>
            <div class="content">
                <div>
                    <input type="checkbox" name="bmb01">
                    <label for="bmb01">Bomba</label>                
                </div>
                <button>Ligar</button>
            </div>
        </div>


    </div>

  
</body>
<script>


    const hdnLED = document.querySelector("#hdnLED");
    const led01 = document.querySelector("#led01");
    const btnOnOff = document.querySelector("#btnonoff");
    getLed();
  
 // document.getElementById('btnonoff').addEventListener('click',()=>{})

    btnOnOff.addEventListener('click',()=>{

        if(led01.checked){
        hdnLED.value = 1
        }else{
        hdnLED.value = 0
        }
    
    })

  function getLed(){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          if(this.responseText == "1"){
            led01.checked = true
          }else{
            led01.checked = false            
          }
        }
      };
      xhttp.open("GET", "/led", true);
      xhttp.send();
  }


</script>
</html>)rawliteral";
