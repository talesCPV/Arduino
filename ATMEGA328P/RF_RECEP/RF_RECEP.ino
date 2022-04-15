// Pino do receptor
#define RX 3
#define LED 13

int arr[80];
int point = 0;

void setup() {
  Serial.begin(9600);
 
  pinMode(RX, INPUT);
  pinMode(LED, OUTPUT); // Define o pino 13 como saída (LED)

}

void loop() {
  // Se o pino RX ficou em alta
  if(digitalRead(RX)){
    arr[point] = 1;
  }else{
    arr[point] = 0;
  }

  point++;
  if(point == sizeof(arr)){
    point = 0;
  }  

  int cont = 0;
  for(int i=0; i<sizeof(arr); i++){
    if(arr[i] == 1){
      cont++;  
    }
  }
    Serial.print(cont);

  if(cont >= (sizeof(arr) / 4)){
    digitalWrite(LED, HIGH);    
    Serial.println(" HIGH");
  }else{
    digitalWrite(LED, LOW);    
    Serial.println(" LOW");
  }
    
  delay(50);
}
