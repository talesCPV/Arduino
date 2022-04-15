
const char indexHTML[] PROGMEM = R"rawliteral(


<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
<style>

body {
  font-family: Arial, Helvetica, sans-serif;
}

button{
  width:100%;
  padding: 10px;
  background-color: #04AA6D;  
}

/* MENU MOBILE */

.mobile-container {
  max-width: 480px;
  margin: auto;
  background-color: #555;
  height: 500px;
  color: white;
  border-radius: 10px;
}

.topnav {
  overflow: hidden;
  background-color: #333;
  position: relative;
}

.topnav #menu {
  display: none;
}

.topnav a {
  color: white;
  padding: 14px 16px;
  text-decoration: none;
  font-size: 17px;
  display: block;
}

.topnav a.icon {
  background: black;
  display: block;
  position: absolute;
  right: 0;
  top: 0;
}

.topnav a:hover {
  background-color: #ddd;
  color: black;
}

.active {
  background-color: #04AA6D;
  color: white;
}

/* CONTENT DISPLAY */

.content{
  padding-left:16px;
  display: none;
}

.content:target{
  display: block;
}

.two-col{
  display: grid;
  grid-template-columns: 1fr 1fr;
}

/* SWITCH CHECKBOX */

.switch_label{
  padding-left: 50px;
  margin-top: 0;
  font-size: xx-large;
  cursor: pointer;
}

.switch {
  position: relative;
  display: flex;
  flex-direction: row;
  width: 60px;
  height: 34px;
  margin: 10px;
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
  background-color: rgb(233, 101, 101);
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
  background-color: #04AA6D;
}


input:checked + .slider:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26px);
  transform: translateX(26px);
}



</style>
</head>
<body onload="javascript:init()">

<!-- Simulate a smartphone / tablet -->
<div class="mobile-container">

<!-- Top Navigation Menu -->
<div class="topnav">
  <a href="#home" class="active">Controle Sitio 1.0</a>
  <div id="menu">
    <a href="#home">Home</a>
    <a href="#luz">Iluminação</a>
    <a href="#port">Porteiras</a>
    <a href="#bomba">Bomba D'água</a>
    <a href="#config">Configuração</a>
  </div>
  <a href="javascript:void(0);" class="icon" onclick="open_menu()">
    <i>☰</i>
  </a>
</div>

<div id="home" class="content">
  <h3>Home</h3>
  <p>This example demonstrates how a navigation menu on a mobile/smart phone could look like.</p>
  <p>Click on the hamburger menu (three bars) in the top right corner, to toggle the menu.</p>
</div>

<div id="luz" class="content">
  <h3>Iluminação</h3>
  <div class="two-col">
    <label class="switch">
      <input type="checkbox" id="luz00">
      <span class="slider"></span>
      <p class="switch_label">Luz01</p>
    </label>
    <label class="switch">
      <input type="checkbox" id="luz01">
      <span class="slider"></span>
      <p class="switch_label">Luz02</p>
    </label>  
    <label class="switch">
      <input type="checkbox" id="luz02">
      <span class="slider"></span>
      <p class="switch_label">Luz03</p>
    </label>
    <label class="switch">
      <input type="checkbox" id="luz03">
      <span class="slider"></span>
      <p class="switch_label">Luz04</p>
    </label> 
    <label class="switch">
      <input type="checkbox" id="luz04">
      <span class="slider"></span>
      <p class="switch_label">Luz05</p>
    </label>
    <label class="switch">
      <input type="checkbox" id="luz05">
      <span class="slider"></span>
      <p class="switch_label">Luz06</p>
    </label> 
    <label class="switch">
      <input type="checkbox" id="luz06">
      <span class="slider"></span>
      <p class="switch_label">Luz07</p>
    </label>
    <label class="switch">
      <input type="checkbox" id="luz07">
      <span class="slider"></span>
      <p class="switch_label">Luz08</p>
    </label>                
  </div>
  <button id="btnLuz">Salvar</button> 
</div>

<div id="port" class="content">
  <h3>Porteiras</h3>
  <p>This example demonstrates how a navigation menu on a mobile/smart phone could look like.</p>
  <p>Click on the hamburger menu (three bars) in the top right corner, to toggle the menu.</p>

  <button id="btnPorta">Salvar</button> 
</div>

<div id="bomba" class="content">
  <h3>Bomba D'água</h3>
  <p>This example demonstrates how a navigation menu on a mobile/smart phone could look like.</p>
  <p>Click on the hamburger menu (three bars) in the top right corner, to toggle the menu.</p>

  <button id="btnBomba">Ligar</button> 
</div>

<div id="config" class="content">
  <h3>Configuração</h3>
  <p>This example demonstrates how a navigation menu on a mobile/smart phone could look like.</p>
  <p>Click on the hamburger menu (three bars) in the top right corner, to toggle the menu.</p>
</div>

<!-- End smartphone / tablet look -->
</div>

<script>
    var Socket;
//    init()
    const frmMain = document.querySelector("#frmMain");
    const btnLuz = document.querySelector("#btnLuz");
    const btnPorta = document.querySelector("#btnPorta");
    const btnBomba = document.querySelector("#btnBomba");
    const menu = document.querySelector("#menu");
    const two = document.querySelector(".two-col");

    fetch("/luz")
    .then((response)=>{
      response.text().then((dados)=>{
        const bin = parseInt(dados).toString(2).padStart(8, '0')
        for(let i=0; i<8; i++){
          if(bin[i]=="1"){
            document.getElementById("luz0"+(7-i)).checked = true;
          }
        }
     })             
    })

    function init() {
      Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
      Socket.onmessage = function(event){
        const dados = event.data;
        console.log(dados);
        
      }
    }

    menu.addEventListener('click',()=>{
      open_menu()
    })

    two.addEventListener('click',()=>{
//        postData("LUZ","0",getCheck("luz0"))
      sendDados("L0")
    })

  btnLuz.addEventListener('click',()=>{
//    postData("LUZ","1",getCheck("luz0"))
    sendDados("L1")
        
  })

  function open_menu() {
    if (menu.style.display === "block") {
      menu.style.display = "none";
    } else {
      menu.style.display = "block";
    }
  }

  function sendDados(param){
    let D;
    if(param[0] == "L"){
      D = getCheck("luz0")
    }

//      console.log(param+D)
      Socket.send(param+D);              
  }
  
/*
  function postData(call,save,dados){
    const param = new URLSearchParams();
      param.append('hdn_call',call);
      param.append('hdn_save',save);
      param.append('hdn_data',dados);
        
    fetch('http://nmcheck.gnome.org/', {
        method: 'POST',
        body: param,
    })
  }
*/

  function getCheck(W){
      let out = ''
      for(let i=0; i<8; i++){
          out += document.querySelector("#"+(W+i).toString()).checked ? '1' : '0'
      }    
      return out    
  }

  btnBomba.addEventListener('click',()=>{
      var url_string = window.location.href
      var url = new URL(url_string);
      var c = url.searchParams.get("hdn_data");
      console.log(c);     
  })


  
  </script>

</body>
</html>

)rawliteral";
