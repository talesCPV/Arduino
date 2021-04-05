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
    
    const spnVel = document.querySelector("#spnVel");
    const spnEsp = document.querySelector("#spnEsp");

    getFrase()

    signupBtn.onclick = (()=>{
      signinForm.style.marginLeft = "-50%";
      signinText.style.marginLeft = "-50%";
    });
    
    signinBtn.onclick = (()=>{
      signinForm.style.marginLeft = "0%";
      signinText.style.marginLeft = "0%";
      return false;
    });


    cmbVel.value = 5;
    cmbEsp.value = 2;


    cmbVel.addEventListener('change',()=>{
      spnVel.innerHTML = (cmbVel.value * 10) + "ms";
    });
    cmbEsp.addEventListener('change',()=>{
      spnEsp.innerHTML = cmbEsp.value;
    });

function getFrase(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        edtFrase.value = this.responseText;
      }
    };
    xhttp.open("GET", "/frase", true);
    xhttp.send();
}

function perm_char(campo){
    const ok_chr = ['1','2','3','4','5','6','7','8','9','0','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','\'','!','@','#','$','%','&','*','(',')','<','>',',','.',';',':','?','/','-','+','=','_'];
    var text = campo.value;
    var out_text = '';
    for(var i = 0; i<text.length; i++){

      if(ok_chr.includes(text.charAt(i))){
        out_text += text.charAt(i);
      }

    }

    campo.value = out_text;
}
