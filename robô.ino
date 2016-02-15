 int optic = 10;                                                                                                                                                                                                                                                 long distancia;
long tempo;
int bswitch = 11;
int estswitch = 0;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
 
void setup() {
  pinMode(IN1, OUTPUT);            //IN1 e IN2 são dos motores A, o qual está na esquerda
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);            //IN3 e IN3 são dos motores B, o qual está na direita
  pinMode(IN4, OUTPUT);
  pinMode(8, INPUT);               //pino 8 está ligado na entrada echo do sensor ultrassônico
  pinMode(9, OUTPUT);              //pino 9 está ligado na entrada trlg do sensor ultrassônico    
  pinMode(optic, INPUT);
  attachInterrupt(0, linha, FALLING);    //interrupção no pino2, quando o sinal alto virar baixo
}
 
void loop() {
  estswitch = digitalRead(bswitch);   
  if (estswitch = HIGH) {            //liga e desliga o robô
    delay(4000);                     //na maioria dos torneios os robôs tem que esperar em média 4 segundos para começar a se mexer
    if (digitalRead(optic) == HIGH) {           //vê se tem alguma linha a frente
      medirdistancia();                         //caso não tenha entra nesse loop
      if (distancia <= 20) {                    //vê se o oponente está a 20cm ou menos de distância
        frente();                               //se ele estiver, entra nesse loop
        delay(100);
      } else {
        parar();                                //caso não esteja a 20cm ou menos, entra nesse loop
        direita();
        frente();
      }
    } 
  }
}

void linha(){
  tras();
  esquerda();
}
 
void medirdistancia() {
  digitalWrite(9, LOW);
  delayMicroseconds(5);
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  tempo = pulseIn(8, HIGH);
  distancia = int(0.017 * tempo);
}
 
void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
 
void tras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
 
void esquerda() {             //liga motor B e desliga motor A (considera-se que o motor A está na esquerda)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}
 
void direita() {              //liga motor A e desliga motor B (considera-se que o motor A está na esquerda)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
 
void parar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
