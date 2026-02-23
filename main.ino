// Projeto 4 - Semáforo inclusivo com display 7 segmentos
 
// Luzes dos carros

int carRed = 12;

int carYellow = 11;

int carGreen = 10;
 
// Luzes dos pedestres

int pedRed = 8;

int pedGreen = 9;
 
// Inclusivo

int buzzer = 7;
 
// Botão

int button = 2;
 
// Display 7 segmentos (ÂNODO COMUM)

int segA = 3;

int segB = 4;

int segC = 5;

int segD = 6;

int segE = A0;

int segF = A1;

int segG = A2;
 
unsigned long changeTime = 0;
 
// Tabela para display ânodo comum (LOW acende)

int digits[10][7] = {

  // A  B  C  D  E  F  G

  {0, 0, 0, 0, 0, 0, 1}, // 0

  {1, 0, 0, 1, 1, 1, 1}, // 1

  {0, 0, 1, 0, 0, 1, 0}, // 2

  {0, 0, 0, 0, 1, 1, 0}, // 3

  {1, 0, 0, 1, 1, 0, 0}, // 4

  {0, 1, 0, 0, 1, 0, 0}, // 5

  {0, 1, 0, 0, 0, 0, 0}, // 6

  {0, 0, 0, 1, 1, 1, 1}, // 7

  {0, 0, 0, 0, 0, 0, 0}, // 8

  {0, 0, 0, 0, 1, 0, 0}  // 9

};
 
void setup() {

  // Carros

  pinMode(carRed, OUTPUT);

  pinMode(carYellow, OUTPUT);

  pinMode(carGreen, OUTPUT);
 
  // Pedestres

  pinMode(pedRed, OUTPUT);

  pinMode(pedGreen, OUTPUT);
 
  // Buzzer

  pinMode(buzzer, OUTPUT);
 
  // Botão

  pinMode(button, INPUT);
 
  // Display

  pinMode(segA, OUTPUT);

  pinMode(segB, OUTPUT);

  pinMode(segC, OUTPUT);

  pinMode(segD, OUTPUT);

  pinMode(segE, OUTPUT);

  pinMode(segF, OUTPUT);

  pinMode(segG, OUTPUT);
 
  // Estado inicial

  digitalWrite(carGreen, HIGH);

  digitalWrite(carYellow, LOW);

  digitalWrite(carRed, LOW);
 
  digitalWrite(pedRed, HIGH);

  digitalWrite(pedGreen, LOW);

  digitalWrite(buzzer, LOW);
 
  clearDisplay();

}
 
void loop() {

  int state = digitalRead(button);
 
  if (state == HIGH && (millis() - changeTime) > 5000) {

    changeLights();

  }
 
  clearDisplay(); // mantém apagado fora da contagem

}
 
void changeLights() {
 
  // Verde desliga direto (sem piscar)

  digitalWrite(carGreen, LOW);
 
  // Amarelo (3s)

  digitalWrite(carYellow, HIGH);

  delay(3000);
 
  // Vermelho

  digitalWrite(carYellow, LOW);

  digitalWrite(carRed, HIGH);

  delay(1000);
 
  // Pedestre verde

  digitalWrite(pedRed, LOW);

  digitalWrite(pedGreen, HIGH);
 
  // Contagem regressiva 5 → 1

  for (int i = 5; i > 0; i--) {

    showDigit(i);
 
    if (i > 2) {

      tone(buzzer, 2500);

      delay(1000);

    } else {

      for (int j = 0; j < 4; j++) {

        tone(buzzer, 2500);

        digitalWrite(pedGreen, HIGH);

        delay(125);

        noTone(buzzer);

        digitalWrite(pedGreen, LOW);

        delay(125);

      }

    }

  }
 
  // Fecha pedestre

  digitalWrite(pedGreen, LOW);

  digitalWrite(pedRed, HIGH);

  noTone(buzzer);

  clearDisplay();
 
  // Volta carros

  digitalWrite(carRed, LOW);

  digitalWrite(carGreen, HIGH);
 
  changeTime = millis();

}
 
void showDigit(int num) {

  digitalWrite(segA, digits[num][0]);

  digitalWrite(segB, digits[num][1]);

  digitalWrite(segC, digits[num][2]);

  digitalWrite(segD, digits[num][3]);

  digitalWrite(segE, digits[num][4]);

  digitalWrite(segF, digits[num][5]);

  digitalWrite(segG, digits[num][6]);

}
 
void clearDisplay() {

  digitalWrite(segA, LOW);

  digitalWrite(segB, LOW);

  digitalWrite(segC, LOW);

  digitalWrite(segD, LOW);

  digitalWrite(segE, LOW);

  digitalWrite(segF, LOW);

  digitalWrite(segG, LOW);

}
 