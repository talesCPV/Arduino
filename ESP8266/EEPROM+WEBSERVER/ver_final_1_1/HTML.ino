
const char indexHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    *{
      margin: 0;
      padding: 0;
      box-sizing: border-box;
      font-family: 'Poppins', sans-serif;
    }
    html,body{
      display: grid;
      height: 100%;
      width: 100%;
      place-items: center;
      background: -webkit-linear-gradient(left, #a445b2, #fa4299);
    }
    ::selection{
      background: #fa4299;
      color: #fff;
    }
    .wrapper{
      overflow: hidden;
      max-width: 390px;
      background: #fff;
      padding: 30px;
      border-radius: 5px;
      box-shadow: 0px 15px 20px rgba(0,0,0,0.1);
    }
    .wrapper .title-text{
      display: flex;
      width: 200%;
    }
    .wrapper .title{
      width: 50%;
      font-size: 35px;
      font-weight: 600;
      text-align: center;
      transition: all 0.6s cubic-bezier(0.68,-0.55,0.265,1.55);
    }
    .wrapper .slide-controls{
      position: relative;
      display: flex;
      height: 50px;
      width: 100%;
      overflow: hidden;
      margin: 30px 0 10px 0;
      justify-content: space-between;
      border: 1px solid lightgrey;
      border-radius: 5px;
    }
    .slide-controls .slide{
      height: 100%;
      width: 100%;
      color: #fff;
      font-size: 18px;
      font-weight: 500;
      text-align: center;
      line-height: 48px;
      cursor: pointer;
      z-index: 1;
      transition: all 0.6s ease;
    }
    .slide-controls label.signup{
      color: #000;
    }
    .slide-controls .slider-tab{
      position: absolute;
      height: 100%;
      width: 50%;
      left: 0;
      z-index: 0;
      border-radius: 5px;
      background: -webkit-linear-gradient(left, #a445b2, #fa4299);
      transition: all 0.6s cubic-bezier(0.68,-0.55,0.265,1.55);
    }
    input[type="radio"]{
      display: none;
    }
    #signup:checked ~ .slider-tab{
      left: 50%;
    }
    #signup:checked ~ label.signup{
      color: #fff;
      cursor: default;
      user-select: none;
    }
    #signup:checked ~ label.login{
      color: #000;
    }
    #login:checked ~ label.signup{
      color: #000;
    }
    #login:checked ~ label.login{
      cursor: default;
      user-select: none;
    }
    .wrapper .form-container{
      width: 100%;
      overflow: hidden;
    }
    .form-container .form-inner{
      display: flex;
      width: 200%;
    }
    .form-container .form-inner form{
      width: 50%;
      transition: all 0.6s cubic-bezier(0.68,-0.55,0.265,1.55);
    }
    .form-inner form .field{
      height: 50px;
      width: 100%;
      margin-top: 20px;
    }
    .form-inner form .field input{
      height: 100%;
      width: 100%;
      outline: none;
      padding-left: 15px;
      border-radius: 5px;
      border: 1px solid lightgrey;
      border-bottom-width: 2px;
      font-size: 17px;
      transition: all 0.3s ease;
    }
    .form-inner form .field input:focus{
      border-color: #fc83bb;
      /* box-shadow: inset 0 0 3px #fb6aae; */
    }
    .form-inner form .field input::placeholder{
      color: #999;
      transition: all 0.3s ease;
    }
    form .field input:focus::placeholder{
      color: #b3b3b3;
    }
    .form-inner form .pass-link{
      margin-top: 5px;
    }
    .form-inner form .signup-link{
      text-align: center;
      margin-top: 30px;
    }
    .form-inner form .pass-link a,
    .form-inner form .signup-link a{
      color: #fa4299;
      text-decoration: none;
    }
    .form-inner form .pass-link a:hover,
    .form-inner form .signup-link a:hover{
      text-decoration: underline;
    }
    form .btn{
      height: 50px;
      width: 100%;
      border-radius: 5px;
      position: relative;
      overflow: hidden;
    }
    form .btn .btn-layer{
      height: 100%;
      width: 300%;
      position: absolute;
      left: -100%;
      background: -webkit-linear-gradient(right, #a445b2, #fa4299, #a445b2, #fa4299);
      border-radius: 5px;
      transition: all 0.4s ease;;
    }
    form .btn:hover .btn-layer{
      left: 0;
    }
    form .btn input[type="submit"]{
      height: 100%;
      width: 100%;
      z-index: 1;
      position: relative;
      background: none;
      border: none;
      color: #fff;
      padding-left: 0;
      border-radius: 5px;
      font-size: 20px;
      font-weight: 500;
      cursor: pointer;
    }
  </style>
  <title> MatrizLed - CONFIG </title>
</head>
<body>

    <div class="wrapper">
      <div class="title-text">
        <div class="title login">
          Matriz de LED
        </div>
        <div class="title signup">
          Config. Rede
        </div>
      </div>
      <div class="form-container">
        <div class="slide-controls">
            <input type="radio" name="slide" id="login" checked>
            <input type="radio" name="slide" id="signup">
            <label for="login" class="slide login"> << </label>
            <label for="signup" class="slide signup"> >> </label>
            <div class="slider-tab"></div>
        </div>
        <div class="form-inner">
          <form action="/" class="login">
            <div class="field">
               <input type="text" name= "edtFrase" id="edtFrase" placeholder="Frase" required>
            </div>
            <div class="field">
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
            </div>
            <div class="pass-link">
              <label> Espaços entre Ciclos</label>
              <select name="cmbEsp">
                <option value="1">1</option>
                <option value="2">2</option>
                <option value="3">3</option>
                <option value="4">4</option>
                <option value="5">5</option>
                <option value="10">10</option>
              </select>
            </div>
            <div class="field btn" id="btnLogin">
              <div class="btn-layer"></div>
              <input type="submit" value="Salvar" >
            </div>
            <div class="signup-link">
              Tales Cembraneli Dantas - 2021
            </div>
          </form>
          <form action="/" class="signup">
            <div class="field">
                <input type="text" name="edtSSID" id="edtSSID" placeholder="Novo Nome da Rede" maxlength="13" minlength="4"required>
            </div>
            <div class="field">
                <input type="password" name="edtNewPass" id="edtNewPass" placeholder="Senha" maxlength="13" minlength="8"required>
            </div>
            <div class="field">
                <input type="password" id="edtNewRepass" placeholder="Repita a Senha" maxlength="13" required>
            </div>
            <div class="field btn" id="btnSignup">
                <div class="btn-layer"></div>
                <input type="submit" value="Salvar">
            </div>
          </form>
        </div>
      </div>
    </div>

  
</body>
<script>

    
    const signinText = document.querySelector(".title-text .login");
    const signinForm = document.querySelector("form.login");
    const signinBtn = document.querySelector("label.login");
    const signupBtn = document.querySelector("label.signup");
    const signupLink = document.querySelector("form .signup-link a");
    const signupForm = document.querySelector("form.signup");
    const btnLogin = document.querySelector("#btnLogin");
    const btnSignup = document.querySelector("#btnSignup");
    
    const edtFrase = document.querySelector("#edtFrase");
    const cmbVel = document.querySelector("#cmbVel");
    const cmbEsp = document.querySelector("#cmbEsp");
    const edtSSID = document.querySelector("#edtSSID");
    const edtNewPass = document.querySelector("#edtNewPass");
    
    signupBtn.onclick = (()=>{
      signinForm.style.marginLeft = "-50%";
      signinText.style.marginLeft = "-50%";
    });
    
    signinBtn.onclick = (()=>{
      signinForm.style.marginLeft = "0%";
      signinText.style.marginLeft = "0%";
      return false;
    });


</script>
</html>)rawliteral";
