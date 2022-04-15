

const char clientHTML[] PROGMEM = R"-**-(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Client</title>

    <style>
        body{
            background-color: rgb(184, 204, 248);
        }



        /* SWITCH CHECKBOX */

        .switch_label{
            padding-left: 50px;
            margin: 0 20px;
            font-size: x-large;
            cursor: pointer;
        }

        .switch {
            position: relative;
            display: flex;
            flex-direction: row;
            white-space: nowrap;
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
            transition: 0.1s;
        }

        button:hover {
            background-color: #000000;
            border: 2px solid #F5F5F5;  
            outline: 5px solid #0a0a0a;          
        }  


    </style>
</head>
<body>
    
    <fieldset>
        <legend id="main-legend">Portas</legend>

        <label class="switch" id="switch00">
            <input type="checkbox" id="chk00">
            <span class="slider"></span>
            <p class="switch_label" id="edt00"></p>
        </label>

        <label class="switch" id="switch01">
            <input type="checkbox" id="chk01">
            <span class="slider"></span>
            <p class="switch_label" id="edt01"></p>
        </label>

        <label class="switch" id="switch02">
            <input type="checkbox" id="chk02">
            <span class="slider"></span>
            <p class="switch_label" id="edt02"></p>
        </label>

        <label class="switch" id="switch03">
            <input type="checkbox" id="chk03">
            <span class="slider"></span>
            <p class="switch_label" id="edt03"></p>
        
        </label>                

        <label class="switch" id="switch04">
            <input type="checkbox" id="chk04">
            <span class="slider"></span>
            <p class="switch_label" id="edt04"></p>
        </label>        

        <label class="switch" id="switch05">
            <input type="checkbox" id="chk05">
            <span class="slider"></span>
            <p class="switch_label" id="edt05"></p>
        </label>     

        <label class="switch" id="switch06">
            <input type="checkbox" id="chk06">
            <span class="slider"></span>
            <p class="switch_label" id="edt06"></p>
        </label>     

        <label class="switch" id="switch07">
            <input type="checkbox" id="chk07">
            <span class="slider"></span>
            <p class="switch_label" id="edt07"></p>
        </label>                     
    </fieldset>

    <button id="btnSalvar">Salvar</button>

</body>
<script>
    var json

    const checkbox = document.querySelectorAll("input[type=checkbox]")
    for(let i=0; i<checkbox.length; i++){
        checkbox[i].addEventListener('change',()=>{
            checkValues()
            postData('/config.json',JSON.stringify(json))
        })
    }

    refreshData()

    function checkValues(){
        for(let i=0; i<8; i++){
            document.getElementById('chk0'+i).checked ?  json.door_value[i] = true :  json.door_value[i] = false 
        }
    }

    function refreshData(){     
      fetch("/savedata")
      .then((response)=>{
        response.text().then((dados)=>{
            json = JSON.parse(dados)
            console.log(json)
            
            document.title = json.name
            document.getElementById('main-legend').innerHTML = json.name
            
            for(let i=0; i<8; i++){

                if(!json.door_enable[i]){
                    document.getElementById('switch0'+i).style = " display: none;"                   
                }else{
                    document.getElementById('chk0'+i).checked = json.door_value[i]
                    document.getElementById('edt0'+i).innerHTML = json.door_name[i]
                }
            }            
        })             
      })
    }

    function postData(file,dados,save='true'){
      const param = new URLSearchParams();
        param.append('file',file);
        param.append('data',dados);
        param.append('save',save);
        
        console.log(
          fetch('/savedata', {
              method: 'POST',
              body: param,
          })
        )
    }

    document.querySelector('#btnSalvar').addEventListener('click',()=>{

        checkValues()
        console.log(JSON.stringify(json))
        postData('/config.json',JSON.stringify(json))

    })

</script>

</html>

)-**-";

const char rootHTML[] PROGMEM = R"-**-(

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <style>

      body{
        background-color: rgb(240, 214, 167);
      }

        h1{
          width: 100vw;
          text-align: center;
        }

        input[type=text], input[type=password]{
            margin: 10px;
        }

        label{
          cursor: pointer;
          font-size: large;
        }

        label:hover{
          color: #04AA6D;
        }

        /* SWITCH CHECKBOX */


        .switch_label{     
            min-width: 70px;
            padding: 7px 0 0 40px;
            margin: 0 20px;        
        }

        .switch {           
            position: relative;
            display: flex;
            flex-direction: row;
            white-space: nowrap;
            width: 60px;
            height: 34px;
            margin: 10px;
        }

        .switch input[type=text], .switch input[type=password]{
          margin: 0 -10px;      
          padding: 5px;         
        }

        .switch input[type=checkbox] { 
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

        .txt{
          padding-left: 0;
        }

        /* BUTTON STYLE */
        button{
            cursor: pointer;
            width: 92vw;
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
            transition: 0.1s;
        }

        button:hover {
            background-color: #000000;
            border: 2px solid #F5F5F5;  
            outline: 5px solid #0a0a0a;          
        }  

    </style>
  </head>
  <body>
      <h1>ROOT CONFIG</h1>
      <fieldset>
        <legend>STATION NAME:</legend>

        <label class="switch" id="switch00">
          <p class="switch_label txt">Name</p>
          <input type="text" id="stat_name" placeholder="Station Name">
        </label> 
          
      </fieldset>

      <fieldset>
        <legend>SSID:</legend>
        <div class="inline">
          <input type="radio" name="modo" id="server" checked>
          <label for="server">Server</label>
          <input type="radio" name="modo" id="client">
          <label for="client">Client</label>
        </div>

        <label class="switch" id="switch00">
          <p class="switch_label txt">ID</p>
          <input type="text" placeholder="Nome da rede" id="ssid">
        </label> 

        <label class="switch" id="switch00">
          <p class="switch_label txt">PASS</p>
          <input type="password" placeholder="Senha da rede" id="pass">
        </label> 

      </fieldset>
       <fieldset>
        <legend>ENABLE DOORS:</legend>
                    
              <label class="switch" id="switch00">
                  <input type="checkbox" id="chk00">
                  <span class="slider"></span>
                  <p class="switch_label">Door 01</p>
                  <input  type="text" placeholder="Name" id="edt00">
              </label>     
              
              <label class="switch" id="switch01">
                  <input type="checkbox" id="chk01">
                  <span class="slider"></span>
                  <p class="switch_label">Door 02</p>
                  <input  type="text" placeholder="Name" id="edt01">
              </label>              
              
              <label class="switch" id="switch02">
                <input type="checkbox" id="chk02">
                <span class="slider"></span>
                <p class="switch_label">Door 03</p>
                <input  type="text" placeholder="Name" id="edt02">
            </label>              
              
            <label class="switch" id="switch03">
              <input type="checkbox" id="chk03">
              <span class="slider"></span>
              <p class="switch_label">Door 04</p>
              <input  type="text" placeholder="Name" id="edt03">
            </label>              
              
            <label class="switch" id="switch04">
              <input type="checkbox" id="chk04">
              <span class="slider"></span>
              <p class="switch_label">Door 05</p>
              <input  type="text" placeholder="Name" id="edt04">
            </label>              
              
            <label class="switch" id="switch05">
              <input type="checkbox" id="chk05">
              <span class="slider"></span>
              <p class="switch_label">Door 06</p>
              <input  type="text" placeholder="Name" id="edt05">
            </label>              
              
            <label class="switch" id="switch06">
              <input type="checkbox" id="chk06">
              <span class="slider"></span>
              <p class="switch_label">Door 07</p>
              <input  type="text" placeholder="Name" id="edt06">
            </label>              
              
            <label class="switch" id="switch07">
              <input type="checkbox" id="chk07">
              <span class="slider"></span>
              <p class="switch_label">Door 08</p>
              <input  type="text" placeholder="Name" id="edt07">
            </label>                           
                        
       </fieldset>
       <button id="btnSave">SAVE CONFIG</button>
  </body>
  <script>

    refreshData()

    function getValues(){
      const out =  new Object
        out.server =  document.querySelector('#server').checked
        out.ssid = document.querySelector('#ssid').value
        out.pass = document.querySelector('#pass').value
        out.name = document.querySelector('#stat_name').value
        out.door_enable = []
        out.door_name = []
        out.door_value = []        

        for(let i=0; i<8; i++){
          out.door_enable.push(document.querySelector('#chk0'+i).checked)
          out.door_name.push(document.querySelector('#edt0'+i).value)
          out.door_value.push(false)          
        }
      console.log(out)
      return JSON.stringify(out)
    }

    document.getElementById('btnSave').addEventListener('click',()=>{

      console.log(getValues())
      postData('/config.json',getValues())

    })


    function postData(file,dados,save='true'){
      const param = new URLSearchParams();
        param.append('file',file);
        param.append('data',dados);
        param.append('save',save);
        
        console.log(
          fetch('/', {
              method: 'POST',
              body: param,
          })
        )
    }

    function refreshData(){     
      fetch("/savedata")
      .then((response)=>{
        response.text().then((dados)=>{
//            console.log(dados)
            const json = JSON.parse(dados)
            console.log(json)

            document.getElementById('stat_name').value = json.name
            document.getElementById('server').checked = json.server
            document.getElementById('client').checked = !json.server
            document.getElementById('ssid').value = json.ssid
            document.getElementById('pass').value = json.pass

            for(let i=0; i<8; i++){
              document.getElementById('chk0'+i).checked = json.door_enable[i]
              document.getElementById('edt0'+i).value = json.door_name[i]
            }

            
        })             
      })
    }

  </script>


</html>

)-**-";


const char indexHTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sitio - Controle 2.0</title>
    <style>

        *{
            box-sizing: border-box;
        }

        body {
            font-size:12px;
            font-family:sans-serif;
            background:#b8e3ef;
            text-align:center;
        }

        textarea, select{
            width: 100%;
            margin: 0;
        }

/*  MENU  */

        .menu {
            position: absolute;
            right: 10px;
            z-index: 100;
            padding:20px;
            background: rgba(255,255,255,.75);
            border-radius:3px;
            color:#6fabbc;
        }

        .menu:hover {
            cursor:pointer;
            background: rgba(255,255,255,.95);            
        }



        .menu-list {            
            list-style: none;
            padding: 0;
            background:#93c7d6;
            max-height: 0;
            max-width: 0;
            transition: all 300ms ;
            overflow: hidden;
            visibility: hidden;
            border-radius:3px;
            opacity:0;
            width: 100%;
            }

        .menu-item a {
            padding:12px 0;
            display: block;
            transition:.25s
        }

        .menu-item a:hover {
            background: #6fabbc;
        }

        a {
            color:#fff;
            text-transform:uppercase;
            text-decoration: none;
        }

        ul.open {
            max-height: 480px;
            max-width: 100%;
            visibility: visible;
            opacity:1;
        }

        /* Main Screen */

        .main-screen{
            position: absolute;
            bottom: 30px;
            z-index: -10;
            padding: 10px;
            border-radius: 15px;
            width: 95%;
            height: calc(100vh - 60px);
            background-color: rgb(22, 21, 21,0.6);
        }

        /* Credit */

        #credit{
            color:rgb(139, 131, 131);
            text-transform:uppercase;
            position: absolute;
            bottom:10px;
            left:50%;
            transform:translateX(-50%);
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
            transition: 0.1s;
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
            bottom: 40px;
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

    <div class="main-screen">

        
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
          
          <div id="contro" class="content">
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

      </div>

    <div>
        <i class="fa fa-bars menu" title="Click me!">☰</i>
        <ul class="menu-list">
            <li class="menu-item" ><a href="#home">Home</a></li>
            <li class="menu-item"><a href="#luz">Iluminação</a></li>
            <li class="menu-item"><a href="#port">Portas</a></li>
            <li class="menu-item"><a href="#contro">Controles</a></li>
            <li class="menu-item"><a href="#config">Configuração</a></li>
        </ul>
    </div>


      

      <a id="credit" href="#home" target="_self">Por Tales C. Dantas - ®2022</a>
    
</body>

<script>

    const frmMain = document.querySelector("#frmMain");
    const btnLuz = document.querySelector("#btnLuz");
    const btnPorta = document.querySelector("#btnPorta");
    const btnBomba = document.querySelector("#btnBomba");
    const btnDevice = document.querySelector("#btnRefresDev");
    const menu = document.querySelector("#menu");
    const two = document.querySelector(".two-col");
    
    let ram;

    refreshDev()
//    refreshDoors()
    refreshData()

    function refreshData(){     
      fetch("/savedata")
      .then((response)=>{
        response.text().then((dados)=>{
//            console.log(dados)
            const json = JSON.parse(dados)
//            console.log(json)
            ram = json
        })             
      })
    }
    
  function makeMenu(){  
    
    const menu = document.querySelector('.menu-list')
    menu.innerHTML = ''

    function addSub(href,desc){
      const a = document.createElement('a')
      a.href = '#'+href
      a.innerHTML = desc

      const li = document.createElement('li')
      li.className = 'menu-item'  
      li.appendChild(a)

      return li
    }

    for(let i=0; i<devs.length; i++){
      menu.appendChild(addSub(devs[i].ip,devs[i].mac))
    }
    
  }

    function refreshDev(){
      
      function addSub(obj,json){
        const a = document.createElement('a')
        a.href = '#'+obj.ip
        a.innerHTML = json.name
  
        const li = document.createElement('li')
        li.className = 'menu-item'  
        li.appendChild(a)
  
        return li
      }
      
      fetch("/devices")
      .then((response)=>{
        response.text().then((dados)=>{
          console.log(dados)        
          const arr = dados.split("\r\n")
          const sel = document.getElementById('cmb-txt')
          const menu = document.querySelector('.menu-list')
          sel.innerHTML = ""
          menu.innerHTML = ''          
          devs = []
          for(let i=1; i<arr.length; i++){
            if(arr[i].trim() != ""){
              const op = document.createElement('option')
              const obj = new Object
              const arr_2 = arr[i].split("|")
              op.innerHTML = arr_2[0]
              op.ip = arr_2[0].toUpperCase()
              op.mac = arr_2[1].toUpperCase()
              obj.ip = arr_2[0].toUpperCase()
              obj.mac = arr_2[1].toUpperCase()
              console.log(op.ip+"/savedata")
              fetch('http://'+op.ip+"/savedata")
              .then((response)=>{
                response.text().then((dados)=>{
                  console.log(dados)
                  json = JSON.parse(dados)              
                  menu.appendChild(addSub(obj,json))                                   
                })
              })
            
              devs.push(obj)
              sel.appendChild(op)
            }
            
          }
//          makeMenu()
// evento de teste de valores      
          sel.addEventListener('click',()=>{      

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

    two.addEventListener('click',()=>{
        postData("LUZ","0",getCheck("luz0"))
    })

  btnLuz.addEventListener('click',()=>{
    postData("LUZ","1",getCheck("luz0"))        
  })
  
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
      console.log(ram)
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

/*  MENU  */
    function toogleMenu(){
        document.querySelector('.menu-list').classList.toggle('open')
    }
    document.querySelector('.menu').addEventListener('click',()=>{
        toogleMenu()
    })
    document.querySelector('.menu-list').addEventListener('click',()=>{
        toogleMenu()
    })
/***********************/

</script>

</body>
</html>

)rawliteral";
