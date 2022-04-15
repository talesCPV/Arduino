
const char indexHTML[] PROGMEM = R"rawliteral(


<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
<style>
* {
  box-sizing: border-box;
}

body {
  font-family: Arial, Helvetica, sans-serif;
  margin: 0;
}

textarea, select{
  width: 100%;
  margin: 0;
}

/* MENU MOBILE */

.mobile-container {
  max-width: 480px;
  margin: auto;
  background-color: #555;
  height: 100vh;
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
  position: fixed;
  background-color: black;
  width: 100%;
  max-width: 480px;
  margin: 0;
  top: 48px;
  z-index: 99;
 
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
  padding:0 16px;
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

/* BUTTON STYLE */
button{
    cursor: pointer;
    background-color: #8457C4;
    color: #F5F5F5;
    font-weight: 600;
    font-size: larger;
    padding: 5px 10px;
    margin: 10px;
    border: 2px solid #F5F5F5;  
    outline: 5px solid #8457C4;          
    transition: 0.4s;
}

button:active {
    transform: scale(0.95);
    transition: 0s;

}

button:hover {
    background-color: #000000;
    border: 2px solid #F5F5F5;  
    outline: 5px solid #0a0a0a;          
}  

/* ALERT */

.alert{
    z-index: 99;
    visibility: hidden;  
    position: fixed;
    background-color: #ffffff;
    border: solid #000000 3px;
    padding: 5px;
    bottom: 10px;
    left: 10px;
    width: calc(100vw - 20px) ;   
    min-height: 100px;      
}

h2 {
    margin-top: 0;
    max-width: calc(100% - 30px);
    color: rgb(163, 59, 59);
    font-family: Tahoma, Arial, sans-serif;
}

.close {
    position: absolute;
    top: 10px;
    right: 10px;
    transition: all 200ms;
    font-size: 30px;
    font-weight: bold;
    text-decoration: none;
    color: #333;
}

.close:hover {
    color: #06D85F;
    cursor: pointer;
}

#alert-content {
    max-height: 30%;
    overflow: auto;
    color: #000000;
}


</style>
</head>
<body>

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
  <label>Devices</label>
  <select id="cmb-txt" size="5"></select> 
  <button id="btnRefresDev">Refresh Devices</button> 
</div>

<div class="alert">
    <h2 id="alert-title"></h2>
    <a class="close" id="close-alert" >&times;</a>
    <div id="alert-content"></div>
</div>


<!-- End smartphone / tablet look -->
</div>

<script>

    const frmMain = document.querySelector("#frmMain");
    const btnLuz = document.querySelector("#btnLuz");
    const btnPorta = document.querySelector("#btnPorta");
    const btnBomba = document.querySelector("#btnBomba");
    const btnDevice = document.querySelector("#btnRefresDev");
    const menu = document.querySelector("#menu");
    const two = document.querySelector(".two-col");

    refreshDev()
    refreshLuz()
    
    function refreshLuz(){
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
    }

    function refreshDev(){
      fetch("/config")
      .then((response)=>{
        response.text().then((dados)=>{        
          const arr = dados.split("\r\n")
          const sel = document.getElementById('cmb-txt')
          sel.innerHTML = ""
          for(let i=1; i<arr.length; i++){
            if(arr[i].trim() != ""){
              const op = document.createElement('option')
              const arr_2 = arr[i].split("|")
              op.innerHTML = arr_2[0]
              op.ip = arr_2[0].toUpperCase()
              op.mac = arr_2[1].toUpperCase()
              sel.appendChild(op)
            }
          }
// evento de teste de valores      
          sel.addEventListener('dblclick',()=>{      

            showAlert(true,"Cadastro de Dispositivos", 
            `            
                <p id="curip">IP:${sel.options[sel.selectedIndex].ip}</p>        
                <p id="macadd">MacID:${sel.options[sel.selectedIndex].mac}</p>        
                <label>Nome</label>
                <input type="text" id="edtDisp">
                <button id="btnSaveMac">Salvar</button>
            
            `,            
            `
                document.getElementById('btnSaveMac').addEventListener('click',()=>{
                    alert('Hello World!!!')
                })            
            `
            
            )
/*
            alert("IP:"+sel.options[sel.selectedIndex].ip)
            alert("MAC:"+sel.options[sel.selectedIndex].mac)
*/      
          })
          
        })             
      })
    }

    btnDevice.addEventListener('click',()=>{
      refreshDev()
    })

    menu.addEventListener('click',()=>{
      open_menu()
    })

    two.addEventListener('click',()=>{
        postData("LUZ","0",getCheck("luz0"))
    })

  btnLuz.addEventListener('click',()=>{
    postData("LUZ","1",getCheck("luz0"))        
  })

  function open_menu() {
    if (menu.style.display === "block") {
      menu.style.display = "none";
      showAlert();
    } else {
      menu.style.display = "block";
    }
  }
  
  function postData(call,save,dados){
    const param = new URLSearchParams();
      param.append('hdn_call',call);
      param.append('hdn_save',save);
      param.append('hdn_data',dados);
        
    fetch('10.10.10.1/', {
        method: 'POST',
        body: param,
    })
  }


  function getCheck(W){
      let out = ''
      for(let i=0; i<8; i++){
          out += document.querySelector("#"+(W+i).toString()).checked ? '1' : '0'
      }    
      return out    
  }

  btnBomba.addEventListener('click',()=>{

      showAlert(true,"Cadastro de Dispositivos", 
      `            
          <p id="macadd"></p>        
          <label>Nome</label>
          <input type="text" id="edtDisp">
          <button id="btnSaveMac">Salvar</button>
      
      `,            
      `
          document.getElementById('btnSaveMac').addEventListener('click',()=>{
              alert('Hello World!!!')
          })            
      `
      
      )

         
  })

  function showAlert(op=false,title='',txt='',js=""){
      if(op){
          document.querySelector('#alert-title').innerHTML = title
          document.querySelector('#alert-content').innerHTML = txt
          eval(js)
          document.querySelector('.alert').style = 'visibility: visible;'
      }else{
          document.querySelector('.alert').style = 'visibility: hidden;'
      }
  }

  document.querySelector('#close-alert').addEventListener('click',()=>{
      showAlert()
  })

</script>

</body>
</html>

)rawliteral";
