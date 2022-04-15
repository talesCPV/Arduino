
const char indexHTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<meta charset="utf-8">
<html>
<head>
<style>

button{
    background-color: rgb(134, 218, 200);
    padding: 10px 20px;
    border-radius: 7px;
    cursor: pointer;
    width: 100%;
}

button:hover{
    background-color: rgba(134, 218, 200, 0.671);
}

p{
    padding-left: 10px;
}

ul {
    position: fixed;
    top: 0;
    width: 100%;
    scroll-behavior: smooth;
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
    background-color: #333;
}

li {
  float: left;
}

li a {
  display: block;
  color: white;
  text-align: center;
  padding: 14px 16px;
  text-decoration: none;
}

li a:hover {
  background-color: #111;
}

.content{
    height: 100vh;
    width: 30%;
    padding-top: 50px;
    margin: auto;
}

/* switch checkbox */

.switch {
  position: relative;
  display: inline-block;
  width: 60px;
  height: 34px;
}

.switch input { 
  opacity: 0;
  width: 0;
  height: 0;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: .4s;
  transition: .4s;
}

.slider:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
}

input:checked + .slider {
  background-color: #21f3bf;
}

input:checked + .slider:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26px);
  transform: translateX(26px);
}

/* Rounded sliders */
.slider.round {
  border-radius: 34px;
}

.slider.round:before {
  border-radius: 50%;
}

</style>
</head>
<body>

  <form id="frmMain">
      <input type="hidden" id="call" name="hdn_call" value="0">
      <input type="hidden" id="data" name="hdn_data" value="00000000">
  </form>

  <ul>
    <li><a class="active" href="#luz">Luz</a></li>
    <li><a href="#bomba">Bomba D'água</a></li>
    <li><a href="#portas">Portas</a></li>
    <li><a href="#sobre">Sobre</a></li>
  </ul>

  <div id="luz" class="content">
      <h1>Iluminação</h1>
      
      <div id="ckbLuz00" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz1" id="luz1">
              <span class="slider round"></span>
          </label>
          <p>Luz 01</p>
      </div>
      <div id="ckbLux01" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz2" id="luz2">
              <span class="slider round"></span>
          </label>
          <p>Luz 02</p>
      </div>
      <div id="ckbLux02" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz3" id="luz3">
              <span class="slider round"></span>
          </label>
          <p>Luz 03</p>
      </div>
      <div id="ckbLux03" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz4" id="luz4">
              <span class="slider round"></span>
          </label>
          <p>Luz 04</p>
      </div>
      <div id="ckbLux04" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz5" id="luz5">
              <span class="slider round"></span>
          </label>
          <p>Luz 05</p>
      </div>
      <div id="ckbLux05" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz6" id="luz6">
              <span class="slider round"></span>
          </label>
          <p>Luz 06</p>
      </div>
      <div id="ckbLux06" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz7" id="luz7">
              <span class="slider round"></span>
          </label>
          <p>Luz 07</p>
      </div>
      <div id="ckbLux07" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="luz8" id="luz8">
              <span class="slider round"></span>
          </label>
          <p>Luz 08</p>
      </div>

      <button id="btnLuz">Salvar</button>
  </div>

  <div id="bomba" class="content">
      <h1>Bomba D'Água</h1>
      
      <div id="ckbBomba00" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" checked>
              <span class="slider round"></span>
          </label>
          <p></p>
      </div>
      <button id="btnBomba">Ligar</button>        
  </div>

  <div id="portas" class="content">
      <h1>Portas</h1>
      <div id="ckbPorta00" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta00" id="porta00">
              <span class="slider round"></span>
          </label>
          <p>Porta 01</p>
      </div>      
      <div id="ckbPorta01" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta01" id="porta01">
              <span class="slider round"></span>
          </label>
          <p>Porta 02</p>
      </div> 
      <div id="ckbPorta02" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta02" id="porta02">
              <span class="slider round"></span>
          </label>
          <p>Porta 03</p>
      </div> 
      <div id="ckbPorta03" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta03" id="porta03">
              <span class="slider round"></span>
          </label>
          <p>Porta 04</p>
      </div> 
      <div id="ckbPorta04" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta04" id="porta04">
              <span class="slider round"></span>
          </label>
          <p>Porta 05</p>
      </div> 
      <div id="ckbPorta05" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta05" id="porta05">
              <span class="slider round"></span>
          </label>
          <p>Porta 06</p>
      </div> 
      <div id="ckbPorta06" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta06" id="porta06">
              <span class="slider round"></span>
          </label>
          <p>Porta 07</p>
      </div> 
      <div id="ckbPorta07" style="display: flex; padding: 10px;">
          <label class="switch">
              <input type="checkbox" name="porta07" id="porta07">
              <span class="slider round"></span>
          </label>
          <p>Porta 08</p>
      </div> 
      <button id="btnPorta">Salvar</button>      
  </div>

  <div id="sobre" class="content">
      <h1>Sobre</h1>
      
  </div>

</body>

<script>

    const frmMain = document.querySelector("#frmMain");

    const btnLuz = document.querySelector("#btnLuz");
    const btnPorta = document.querySelector("#btnPorta");
    const btnBomba = document.querySelector("#btnBomba");


    fetch("/luz")
    .then((response)=>{
      response.text().then((dados)=>{
        const bin = parseInt(dados).toString(2).padStart(8, '0')
        for(let i=0; i<8; i++){
          if(bin[i]=="1"){
            document.getElementById("luz"+(8-i)).checked = true;
          }
        }

     })             
    })

    function getCheck(W){
        let out = ''
        for(let i=0; i<8; i++){
            out += document.querySelector("#"+W+(i+1).toString()).checked ? '1' : '0'
        }    
        return out    
    }

    btnLuz.addEventListener('click',()=>{
        document.querySelector("#call").value = "LUZ"       
        document.querySelector("#data").value = getCheck("luz")
        frmMain.submit()        
    })

    btnPorta.addEventListener('click',()=>{
        document.querySelector("#call").value = "PORTA"
        document.querySelector("#data").value = getCheck("prt")
        frmMain.submit()
    })

    btnBomba.addEventListener('click',()=>{
        var url_string = window.location.href
        var url = new URL(url_string);
        var c = url.searchParams.get("hdn_data");
        console.log(c);     
    })

</script>


</html>

)rawliteral";
