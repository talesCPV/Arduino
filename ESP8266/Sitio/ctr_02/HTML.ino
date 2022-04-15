
const char indexHTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en">
<head>
<title>Mobile</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>

    *{
        text-decoration: none;
        color: inherit;
        margin: 0;
        padding: 0;
        scroll-behavior: smooth;
    }

    .main{
        display: flex;
        flex-direction: column;
    }

    .sub{
        height: 100vh;
        width: 100%;
        background-color: rgb(185, 204, 204);
    }

    .head{
        min-height: 50px;
        padding: 20px;
        background-color: darkmagenta;
        display: flex;
        justify-content: space-around;
        flex-direction: row;
        font-size: larger;
    }

    .up{
        border: 1px solid;
    }

    .content{
        padding: 20px;
    }

    @media only screen and (max-width: 700px) {
        .main{
            flex-direction: column;
        }
    }

</style>
</head>
<body>

    <form id="frmMain">
        <input type="hidden" id="call" name="hdn_call" value="0">
        <input type="hidden" id="data" name="hdn_data" value="00000000">
    </form>


    <div id="top" class="main">

        <div class="sub">
            <div class="head">
                <h2>  <a href="#luz">Luz</a> </h2>
                <h2>  <a href="#portas">Portas</a> </h2>
                <h2>  <a href="#bomba">Bomba</a> </h2>
           
            </div>

            <p>Controle universal do Sítio</p>

        </div>
        <div id="luz" class="sub">
            <div class="head">
                <h1>Luz</h1>
                <h1 class="up"> <a href="#top">↑</a> </h1> 
            </div>
            <div class="content">
                <div>
                    <input type="checkbox" name="luz1" id="luz1">
                    <label for="luz1">Luz 01</label>
                </div>
                <div>
                    <input type="checkbox" name="luz2" id="luz2">
                    <label for="luz2">Luz 02</label>
                </div>
                <div>
                    <input type="checkbox" name="luz3" id="luz3">
                    <label for="luz3">Luz 03</label>
                </div>
                <div>
                    <input type="checkbox" name="luz4" id="luz4">
                    <label for="luz4">Luz 04</label>
                </div>
                <div>
                    <input type="checkbox" name="luz5" id="luz5">
                    <label for="luz5">Luz 05</label>
                </div>
                <div>
                    <input type="checkbox" name="luz6" id="luz6">
                    <label for="luz6">Luz 06</label>
                </div>
                <div>
                    <input type="checkbox" name="luz7" id="luz7">
                    <label for="luz7">Luz 07</label>
                </div>
                <div>
                    <input type="checkbox" name="luz8" id="luz8">
                    <label for="luz8">Luz 08</label>
                </div>

                <button id="btnLuz">Salvar</button>

            </div>        
        </div>
        <div id="portas" class="sub">
            <div class="head">
                <h1>Portas</h1>
                <h1 class="up"> <a href="#top">↑</a> </h1> 
            </div>

            <div class="content">
                <div>
                    <input type="checkbox" name="prt1" id="prt1">
                    <label for="prt1">Porta 01</label>
                </div>
                <div>
                    <input type="checkbox" name="prt2" id="prt2">
                    <label for="prt2">Porta 02</label>
                </div>
                <div>
                    <input type="checkbox" name="prt3" id="prt3">
                    <label for="prt3">Porta 03</label>
                </div>
                <div>
                    <input type="checkbox" name="prt4" id="prt4">
                    <label for="prt4">Porta 04</label>
                </div>
                <div>
                    <input type="checkbox" name="prt5" id="prt5">
                    <label for="prt5">Porta 05</label>
                </div>
                <div>
                    <input type="checkbox" name="prt6" id="prt6">
                    <label for="prt6">Porta 06</label>
                </div>
                <div>
                    <input type="checkbox" name="prt7" id="prt7">
                    <label for="prt7">Porta 07</label>
                </div>
                <div>
                    <input type="checkbox" name="prt8" id="prt8">
                    <label for="prt8">Porta 08</label>
                </div>   

                <button id="btnPorta">Salvar</button>

            </div>


        </div>
        <div id="bomba" class="sub">
            <div class="head">
                <h1>Bomba D´Água</h1>
                <h1 class="up"> <a href="#top">↑</a> </h1> 
            </div>
            <div class="content">
                <div>
                    <input type="checkbox" name="bmb01">
                    <label for="bmb01">Bomba</label>                
                </div>
                <button id="btnBomba">Ligar</button>
            </div>
        </div>


    </div>

    <script>

    const frmMain = document.querySelector("#frmMain");

    const btnLuz = document.querySelector("#btnLuz");
    const btnPorta = document.querySelector("#btnPorta");
    const btnBomba = document.querySelector("#btnBomba");

   console.log(getData('luz'))
   console.log(getData('porta'))
   console.log(getData('bomba'))

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


    function getData(N){
        var xhttp = new XMLHttpRequest();
        var out = ''
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            out = this.responseText;
            }
        };
        xhttp.open("GET", "/"+N, true);
        xhttp.send();

        return out
    }

    </script>

</body>
</html>

)rawliteral";
