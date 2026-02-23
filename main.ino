// Luzes dos carros
int carRed = 12;
int carYellow = 11;
int carGreen = 10;
 
// Luzes dos pedestres
int pedRed = 8;
int pedGreen = 9;
 
// Inclusivo
int buzzer = 7; // sinal sonoro para pessoas cegas
 
// Botão
int button = 2;
 
// Display 7 segmentos (pinos)
int segA = 3;
int segB = 4;
int segC = 5;
int segD = 6;
int segE = A0;
int segF = A1;
int segG = A2;
 
// Tempo de travessia
int crossTime = 5000;
 
unsigned long changeTime = 0;
 
// Para display de ÂNODO COMUM (segmentos acendem com LOW)
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
 
  // Inclusivo
  pinMode(buzzer, OUTPUT);
 
  // Botão
  pinMode(button, INPUT);
  // Display 7 segmentos
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
  // Desliga display no início
  clearDisplay();
}
 
void loop() {
  int state = digitalRead(button);
 
  // Só muda se botão for pressionado e tiver passado 5 segundos
  if (state == HIGH && (millis() - changeTime) > 5000) {
    changeLights();
  }
  // Mantém display apagado quando não está em contagem
  clearDisplay();
}
 
void changeLights() {
  // Verde piscando para carros (3 segundos)
  for (int i = 0; i < 6; i++) {
    digitalWrite(carGreen, LOW);
    delay(250);
    digitalWrite(carGreen, HIGH);
    delay(250);
  }
 
  // Amarelo para carros (3 segundos)
  digitalWrite(carGreen, LOW);
  digitalWrite(carYellow, HIGH);
  delay(3000);
 
  // Vermelho para carros
  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, HIGH);
  delay(1000); // tempo de segurança
 
  // Verde para pedestres
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);
 
  // Contagem regressiva durante travessia (5 segundos)
  for (int i = 5; i > 0; i--) {
    showDigit(i);
    if (i > 2) {
      // Primeiros 3 segundos: tom contínuo
      tone(buzzer, 2500);
      delay(1000);
    } else {
      // Últimos 2 segundos: som intermitente com display piscando
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
 
  // Volta para verde dos carros
  digitalWrite(carRed, LOW);
  digitalWrite(carGreen, HIGH);
 
  changeTime = millis();
}
 
void showDigit(int num) {
  // Ativa os segmentos conforme o dígito desejado
  digitalWrite(segA, digits[num][0]);
  digitalWrite(segB, digits[num][1]);
  digitalWrite(segC, digits[num][2]);
  digitalWrite(segD, digits[num][3]);
  digitalWrite(segE, digits[num][4]);
  digitalWrite(segF, digits[num][5]);
  digitalWrite(segG, digits[num][6]);
}
 
void clearDisplay() {
  // Desliga todos os segmentos
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}