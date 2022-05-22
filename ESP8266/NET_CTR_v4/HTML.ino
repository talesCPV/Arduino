/***************  ROOT HTML *****************/

const char rootHTML[] PROGMEM = R"-**-(


<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1, user-scalable=0">
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

        select{
          min-width: 160px;
          margin-left: 30px;
        }

        textarea{
          width: 87vw;            
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

        .width{
          width : 30px;
          margin: 0 5px  !important;
        }

        .door-name{
          max-width: 150px !important; 
        }

    </style>
  </head>
  <body>
      <h1>ROOT CONFIG</h1>
      <fieldset>
        <legend>STATION NAME:</legend>

        <label class="switch">
          <p class="switch_label txt">Name</p>
          <input type="text" id="stat_name" placeholder="Station Name">
        </label> 
          
      </fieldset>

      <fieldset>
        <legend>SSID:</legend>
        <div>
          <input type="radio" name="modo" id="server" checked>
          <label for="server">Server</label>
          <input type="radio" name="modo" id="client">
          <label for="client">Client</label>
        </div>

        <label class="switch">
          <p class="switch_label txt">ID</p>
          <input type="text" placeholder="Nome da rede" id="ssid">
        </label> 

        <label class="switch">
          <p class="switch_label txt">PASS</p>
          <input type="password" placeholder="Senha da rede" id="pass">
        </label> 

        <label class="switch" >
          <p class="switch_label txt" style="min-width: 57px">IP</p>
          <input type="text" id="ip_1" class="width" maxlength="3">
          <input type="text" id="ip_2" class="width" maxlength="3">
          <input type="text" id="ip_3" class="width" maxlength="3">
          <input type="text" id="ip_4" class="width" maxlength="3">
        </label> 
        
      </fieldset>
       <fieldset>
        <legend>ENABLE DOORS:</legend>

        <label class="switch">
          <p class="switch_label" style="padding: 7px 0 0 10px;">Key Position</p>
          <select class="door-name" id="cmbInvert">
            <option value="0">Normal</option>
            <option value="1">Invert</option>
          </select>
        </label>  
                  
        <label class="switch">
            <input type="checkbox" id="chk00">
            <span class="slider"></span>
            <p class="switch_label">Door 01</p>
            <input class="door-name" type="text" placeholder="Name" id="edt00" maxlength="15">
        </label>     
        
        <label class="switch">
            <input type="checkbox" id="chk01">
            <span class="slider"></span>
            <p class="switch_label">Door 02</p>
            <input class="door-name" type="text" placeholder="Name" id="edt01" maxlength="15">
        </label>              
        
        <label class="switch">
          <input type="checkbox" id="chk02">
          <span class="slider"></span>
          <p class="switch_label">Door 03</p>
          <input class="door-name" type="text" placeholder="Name" id="edt02" maxlength="15">
        </label>              
          
        <label class="switch">
          <input type="checkbox" id="chk03">
          <span class="slider"></span>
          <p class="switch_label">Door 04</p>
          <input class="door-name" type="text" placeholder="Name" id="edt03" maxlength="15">
        </label>              
          
        <label class="switch">
          <input type="checkbox" id="chk04">
          <span class="slider"></span>
          <p class="switch_label">Door 05</p>
          <input class="door-name" type="text" placeholder="Name" id="edt04" maxlength="15">
        </label>              
          
        <label class="switch">
          <input type="checkbox" id="chk05">
          <span class="slider"></span>
          <p class="switch_label">Door 06</p>
          <input class="door-name" type="text" placeholder="Name" id="edt05" maxlength="15">
        </label>              
          
        <label class="switch">
          <input type="checkbox" id="chk06">
          <span class="slider"></span>
          <p class="switch_label">Door 07</p>
          <input class="door-name" type="text" placeholder="Name" id="edt06" maxlength="15">
        </label>              
          
        <label class="switch">
          <input type="checkbox" id="chk07">
          <span class="slider"></span>
          <p class="switch_label">Door 08</p>
          <input class="door-name" type="text" placeholder="Name" id="edt07" maxlength="15">
        </label>                           

        <p> Twin Doors ex:1,2,5 (each twins for line)</p>
        <textarea rows="10" id="txtTwins"></textarea>       
                        
       </fieldset>
       <button id="btnSave">SAVE CONFIG</button>
       <button id="btnReset">RESET DEVICE</button>
  </body>
  <script>

    document.getElementById('btnReset').addEventListener('click',()=>{
      fetch('/reset', {
          method: 'POST'
      })
    })


    refreshData()

    function getValues(){
      const out =  new Object
        out.ram = '0'
        out.ram += document.querySelector('#server').checked ? '1' : '0'
        out.ram += document.querySelector('#cmbInvert').value
        out.ram += '00000'
        out.ssid = document.querySelector('#ssid').value
        out.pass = document.querySelector('#pass').value
        out.name = document.querySelector('#stat_name').value
        out.door_enable = ''
        out.door_name = []
        out.door_value = '00000000'
        out.ip = []
        out.ip.push(parseInt(document.querySelector('#ip_1').value))
        out.ip.push(parseInt(document.querySelector('#ip_2').value))
        out.ip.push(parseInt(document.querySelector('#ip_3').value))
        out.ip.push(parseInt(document.querySelector('#ip_4').value))        
        out.twins = document.querySelector('#txtTwins').value

        for(let i=0; i<8; i++){
          out.door_enable += document.querySelector('#chk0'+i).checked ? '1' : '0'
          out.door_name.push(document.querySelector('#edt0'+i).value)
        }
      console.log(out)
      return JSON.stringify(out)
    }

    document.getElementById('btnSave').addEventListener('click',()=>{

      console.log(getValues())
      postData('/config.json',getValues())

    })


    function postData(file,dados,act='save'){
      const param = new URLSearchParams();
        param.append('file',file);
        param.append('data',dados);
        param.append('act',act);
        param.append('org','root');
        
        fetch('/savedata', {
            method: 'POST',
            body: param,
        })       
    }

    function refreshData(){     
      fetch("/json")
      .then((response)=>{
        response.text().then((dados)=>{
            console.log(dados)
            const json = JSON.parse(dados)
            console.log(json)
             console.log(parseInt(json.ram[1]))            

            document.getElementById('stat_name').value = json.name
            document.getElementById('server').checked = parseInt(json.ram[1])
            document.getElementById('client').checked = !parseInt(json.ram[1])
            document.getElementById('ssid').value = json.ssid
            document.getElementById('pass').value = json.pass
            document.getElementById('ip_1').value = json.ip[0]
            document.getElementById('ip_2').value = json.ip[1]
            document.getElementById('ip_3').value = json.ip[2]
            document.getElementById('ip_4').value = json.ip[3]
            document.getElementById('cmbInvert').value = json.ram[2]
            document.getElementById('txtTwins').value = json.twins

            for(let i=0; i<8; i++){
              document.getElementById('chk0'+i).checked = parseInt(json.door_enable[i])
              document.getElementById('edt0'+i).value = json.door_name[i]
            }
            
        })             
      })
    }

  </script>


</html>

)-**-";
/***********************************************/
/***********************************************/
/****************  CLIENT HTML *****************/
/***********************************************/
/***********************************************/


const char clientHTML[] PROGMEM = R"-**-(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Client</title>

    <style>

        *{
            box-sizing: border-box;
        }
            
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
    var bin

    const checkbox = document.querySelectorAll("input[type=checkbox]")
    
    for(let i=0; i<checkbox.length; i++){
        checkbox[i].addEventListener('change',()=>{
            checkValues()
            postData('/config.json',JSON.stringify(json))
        })
    }

    refreshData()

    function checkValues(){
        let door = ''
        for(let i=0; i<8; i++){
          door += document.getElementById('chk0'+i).checked ? 1 : 0        
        }
        json.door_value = door
    }

    function refreshData(){
      const ram = fetch("/ram")    
      ram.then((resp_ram)=>{
        resp_ram.text().then((raw_bin)=>{
          bin = raw_bin.split('\r\n')
          console.log(bin)        
          const database = fetch("/json")        
          database.then((resp_json)=>{
            resp_json.text().then((raw_data)=>{
              json = JSON.parse(raw_data)
              console.log(json)
              for(let i=0; i<8; i++){

                document.getElementById('switch0'+i).style = parseInt(json.door_enable[i]) ? "" : " display: none;"
                document.getElementById('chk0'+i).checked = parseInt(json.door_value[i])
                document.getElementById('edt0'+i).innerHTML = json.door_name[i]
               
              }                  
            })
          })        
        })      
      })           
    }

    function postData(file,dados,act='save'){
      const param = new URLSearchParams();
        param.append('file',file);
        param.append('data',dados);
        param.append('act',act);
        param.append('org','client');
                
        fetch('/savedata', {
            method: 'POST',
            body: param,
        })       
    }

    document.querySelector('#btnSalvar').addEventListener('click',()=>{

        checkValues()
        console.log(JSON.stringify(json))
        postData('/config.json',JSON.stringify(json))

    })

</script>

</html>

)-**-";

/*********************************************/
/*********************************************/
/***************  INDEX HTML *****************/
/*********************************************/
/*********************************************/


const char indexHTML[] PROGMEM = R"rawliteral(


<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1, user-scalable=0">
    <title>Sitio - Controle 2.0</title>
    <style>
  
        *{
            box-sizing: border-box;
        }

        body {
            font-size:12px;
            font-family: sans-serif;
            background:#EBE1B5;
            text-align:center;
        }

        textarea, select{
            width: 100%;
            margin: 0;
        }

        fieldset{
          border-radius: 10px;
          margin-top: 50px;
          font-size: x-large;
          font-weight: 500;
          color: rgb(56, 55, 55);
      
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
            background-color: #DBD2AD;
        }

        /* Credit */

        #credit{
            color:rgb(77, 72, 72);
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

        /* SWITCH CHECKBOX */

        .switch_label{
            padding-left: 60px;
            margin-top: 0;
            font-size: xx-large;
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

    <div class="main-screen"></div>

    <div>
        <i class="menu" title="Main Menu">☰</i>
        <ul class="menu-list"></ul>
    </div>
    <a id="credit" href="#home" target="_self">Por Tales C. Dantas - ®2022</a>
    
    <div class="alert">
      <h2 id="alert-title"></h2>
      <a class="close" id="close-alert" >&times;</a>
      <div id="alert-content"></div>
    </div>

    
</body>

<script>

    const frmMain = document.querySelector("#frmMain");
    const menu = document.querySelector("#menu");
    
    let ram;
    let ip;

    refreshDev()
    refreshData()

    function refreshData(){
      console.log('refreshData()')     
      fetch("/json")
      .then((response)=>{
        response.text().then((dados)=>{
            console.log(dados)
            const json = JSON.parse(dados)
            console.log(json)
        })             
      })
    }

    function checkValues(){
       const invert = parseInt(ram.ram[2]) ? true : false
       let door = ''
        for(let i=0; i<ram.door_enable.length; i++){
          if (ram.door_enable[i] == '1'){

              if((document.getElementById('chk0'+i).checked && !invert)||(!document.getElementById('chk0'+i).checked && invert)){
                door += 1                  
              }else{
                door += 0
              }
          }else{
            door += 0
          }
        }
        ram.door_value = door
    }

    function openHTML(IP){
      fetch('http://'+IP+'/json', {
        method : 'GET',
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json',
          'Host': '10.10.10.1'
        }                
      })
      .then((response)=>{
        response.text().then((dados)=>{          
          ram = JSON.parse(dados)
          const invert = parseInt(ram.ram[2]) ? true : false
          let body = `<fieldset> <legend id="main-legend">${ram.name}</legend>`
          for(let i=0; i<ram.door_enable.length; i++){
            if (ram.door_enable[i] == '1'){
              
              let check = ''
              if((parseInt(ram.door_value[i]) && !invert)||(!parseInt(ram.door_value[i]) && invert) ){
                check = 'checked'
              }
              body += `
                <label class="switch">
                    <input type="checkbox" id="chk0${i}" ${check}>
                    <span class="slider"></span>
                    <p class="switch_label" id="edt0${i}">${ram.door_name[i]}</p>
                </label>
              `
            }
          }
          body += '</fieldset>'

          document.querySelector('.main-screen').innerHTML = body

          const checkbox = document.querySelectorAll('input[type=checkbox]')
          
          for(let i=0; i<checkbox.length; i++){
            checkbox[i].addEventListener('change',()=>{
                twins(checkbox[i].id)
                checkValues()
                postData(ip,JSON.stringify(ram))
            })
          }
        })
      })
    }

    function twins(N){ // N = checkbox id
        const state = document.getElementById(N).checked ? 1 : 0
        const pin = N.substr(N.length-1,N.length)
        const twins = ram.twins.split('\n') 
        for(let i=0; i<twins.length; i++){
            const line = twins[i].split(',')
            if(line.includes(pin)){
                for(let j=0; j<line.length; j++){
                    if(document.getElementById('chk0'+line[j]) != null){
                      document.getElementById('chk0'+line[j]).checked = state ? true :  false                    
                    }
                }
            }
        }
    }


    function refreshDev(){
     console.log('refreshDev()') 
         
      function addSub(obj){
        const a = document.createElement('a')
        a.href = '#'+obj.ip
        a.innerHTML = obj.name
  
        const li = document.createElement('li')
        li.className = 'menu-item'  
        li.appendChild(a)

        li.addEventListener('click',()=>{
          ip = obj.ip
          openHTML(obj.ip)
        })
  
        return li
      }
      
      fetch("/devices")
      .then((response)=>{
        response.text().then((dados)=>{
          console.log(dados)        
          const arr = dados.split("\r\n")
          const menu = document.querySelector('.menu-list')
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
              console.log(op.ip+"/json")
           
              fetch('http://'+op.ip+'/json', {
                method : 'GET',
                headers: {
                  'Accept': 'application/json',
                  'Content-Type': 'application/json',
                  'Host': '10.10.10.1'
                }                
              })
              .then((response)=>{
                response.text().then((dados)=>{
                  console.log(dados)
                  json = JSON.parse(dados)
                  obj.name = json.name              
                  menu.appendChild(addSub(obj))
                  devs.push(obj)                                   
                })
              })                            
            }            
          }              
        })             
      })
    }
    
    function postData(ip,dados){
      const param = new URLSearchParams();
        param.append('file','/config.json');
        param.append('data',dados);
        param.append('act','save');
        param.append('org','server');
               
      fetch('http://'+ip+'/savedata', {
        method : 'POST',
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

/**********  MENU  **********/

    function toogleMenu(){
        document.querySelector('.menu-list').classList.toggle('open')
    }
    document.querySelector('.menu').addEventListener('click',()=>{
        toogleMenu()
    })
    document.querySelector('.menu-list').addEventListener('click',()=>{
        toogleMenu()
    })

</script>

</body>
</html>

)rawliteral";
