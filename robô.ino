//coloco ou nao coloco o botao de desligar e ligar o robo?
const byte optic = 3; //2 resistores de 10k e um d 300
const byte IN1 = 4;
const byte IN2 = 5;
const byte IN3 = 6;
const byte IN4 = 7;
const byte echo = 8;
const byte trig = 9;
//----------------------------------------------------------
long distancia;
float tempo;
int ligado = 0;
//----------------------------------------------------------
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(optic, INPUT);
  attachInterrupt(1, linha, LOW); //porta 2 - chama sempre q for 0
  delay(4000);
}
//----------------------------------------------------------
void loop() {
  medirdistancia();
  if (distancia <= 25) {
    frente(255);
    delay(50);
  } else {
    direcao(120,100);
  }
}
//----------------------------------------------------------
void linha() {
  tras(200);
  esquerda(120);
}
//----------------------------------------------------------
void medirdistancia() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  tempo = pulseIn(echo, HIGH);
  distancia = int(0.018 * tempo);
}
//----------------------------------------------------------
void direcao(int velocidade, int duracao) {
  long numero = rand(0, 30);
  if (numero <= 10) {
    esquerda(velocidade);
    delay(duracao);
    frente(velocidade);
    delay(duracao*0,7);
    parar();
  }
  if (numero > 10 && numero <= 20 ) {
    direita(velocidade);
    delay(duracao);
    frente(velocidade);
    delay(duracao*0,7);
    parar();
  }
  else {
    frente(velocidade);
    delay(duracao);
    parar();
  }
}
//----------------------------------------------------------
void tras(int velocidade) {
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}
//----------------------------------------------------------
void frente(int velocidade) {
  analogWrite(IN1, 0);
  analogWrite(IN2, velocidade);
  analogWrite(IN3, 0);
  analogWrite(IN4, velocidade);
}
//----------------------------------------------------------
void direita(int velocidade) {
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
  analogWrite(IN1, velocidade);
  analogWrite(IN2, velocidade);
}
//----------------------------------------------------------
void esquerda(int velocidade) {
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);
  analogWrite(IN3, velocidade);
  analogWrite(IN4, velocidade);
}
//----------------------------------------------------------
void parar() {       //ou tudo low
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
