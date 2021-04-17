//Programa : Elsie 2019 - tartaruga busca-luz
//Inspirada no trabalho de William Grey Walter
//Autor: Gino Passos
 
//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1  = 4;
int IN2  = 5;
int IN3  = 6;
int IN4  = 7;
int EN_A = 10;      //Enable pin for first motor
int EN_B = 11;      //Enable pin for second motor
int motor_speed=200;
int sensorPin0   = A0;  // Pinos dos sensores de luminosidade
int sensorValue0 = 0;
int sensorPin1   = A1;
int sensorValue1 = 0;

void leftTURN();
void rightTURN();
void aheadGO();

void setup()
{
  //Define os pinos como saida
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 Serial.begin(9600);
}
  
void loop()
{
  sensorValue0 = analogRead(sensorPin0);  // "olho" esquerdo
  sensorValue1 = analogRead(sensorPin1);  // "olho" direito

  float fVal0 = 100. * ( (float) sensorValue0 )/1300;
  float fVal1 = 100. * ( (float) sensorValue1 )/1600;

  float lumin;
  int turnLEFT  = 0;
  int turnRIGHT = 0;
  int goAHEAD   = 1;

  lumin = (fVal0 + fVal1)/2;

  fVal0 = 100. * (fVal0/lumin);
  fVal1 = 100. * (fVal1/lumin);

  float aux = fVal0 - fVal1;

  if(aux > 15) {
    turnLEFT = 1; goAHEAD = 0;
  }
  if(aux < -15) {
    turnRIGHT = 1; goAHEAD = 0;
  }

  Serial.print(0);
  Serial.print(",");
  Serial.print(turnLEFT);
  Serial.print(",");
  Serial.print(turnRIGHT);
  Serial.print(",");
  Serial.print(goAHEAD);
  Serial.print(",");
  Serial.print(fVal0);
  Serial.print(",");
  Serial.println(fVal1);

  if (turnLEFT == 1)  leftTURN();
  if (turnRIGHT == 1) rightTURN();
  if (goAHEAD == 1)   aheadGO();

  delay(900);
}


void leftTURN() {
 //Gira o Motor B no sentido anti-horario
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 analogWrite(EN_B, motor_speed);
 delay(50);

 //PARA os Motores A e B
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 analogWrite(EN_A, motor_speed);
 analogWrite(EN_B, motor_speed);
}


void rightTURN() {
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 analogWrite(EN_A, motor_speed);
 delay(50);

 //PARA os Motores A e B
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 analogWrite(EN_A, motor_speed);
 analogWrite(EN_B, motor_speed);
}


void aheadGO() {
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 //Gira o Motor B no sentido anti-horario
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 analogWrite(EN_A, motor_speed);
 analogWrite(EN_B, motor_speed);
 delay(50);

 //PARA os Motores A e B
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 analogWrite(EN_A, motor_speed);
 analogWrite(EN_B, motor_speed);
}
