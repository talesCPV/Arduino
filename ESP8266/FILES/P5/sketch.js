

document.getElementById('defaultCanvas0').style.margin = "auto";

const screen = [300,455];

const ball =  new Object;
  ball.x = 10;
  ball.y = 10;
  ball.hor = true;
  ball.ver = true;


function setup() {
    createCanvas(screen[0], screen[1]);
    stroke(255);
    fill(255)
}

function draw() {
    background(0);   
    textSize(30); // tamanho da fonte
    text("PONG", 110, 100);

    circle(ball.x,ball.y,15);

    move();

}

function move(){

  const speed = 5;

  ball.hor ? ball.x+= speed : ball.x-= speed;
  ball.ver ? ball.y+= speed : ball.y-= speed;

  bounds();

}

function bounds(){

  const edge = 5;

  if(ball.x >= screen[0] - edge){
    ball.hor = false;
  }else if(ball.x <= edge){
    ball.hor = true;
  }

  if(ball.y >= screen[1] - edge){
    ball.ver = false;
  }else if(ball.y <= edge){
    ball.ver = true;
  }

}