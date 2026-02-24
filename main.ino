// Semáforo inclusivo com display 7 segmentos (CÁTODO COMUM)
// Carros automáticos + botão adianta para pedestre
 
// Luzes dos carros
int carRed = 12;
int carYellow = 11;
int carGreen = 10;
 
// Luzes dos pedestres
int pedRed = 8;
int pedGreen = 9;
 
// Buzzer
int buzzer = 7;
 
// Botão
int button = 2;
 
// Display 7 segmentos (CÁTODO COMUM)
int segA = 3;
int segB = 4;
int segC = 5;
int segD = 6;
int segE = A0;
int segF = A1;
int segG = A2;
 
// Tempos automáticos
unsigned long greenTime = 10000;
unsigned long yellowTime = 2000;
unsigned long lastChange = 0;
 
int state = 0;
// 0 = Verde carros
// 1 = Amarelo carros
// 2 = Vermelho carros (pedestre aberto)
 
 
// Tabela CÁTODO COMUM (HIGH acende)
int digits[10][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}  //9
};
 
void setup() {
 
  pinMode(carRed, OUTPUT);
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
 
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
 
  // Estado inicial
  digitalWrite(carGreen, HIGH);
  digitalWrite(pedRed, HIGH);
 
  lastChange = millis();
}
 
void loop() {
 
  unsigned long currentMillis = millis();
 
  // BOTÃO adianta o verde
  if (digitalRead(button) == HIGH && state == 0) {
    state = 1; // vai para amarelo
    lastChange = currentMillis;
    digitalWrite(carGreen, LOW);
    digitalWrite(carYellow, HIGH);
  }
 
  switch(state) {
 
    case 0: // Verde carros
      if (currentMillis - lastChange >= greenTime) {
        state = 1;
        lastChange = currentMillis;
        digitalWrite(carGreen, LOW);
        digitalWrite(carYellow, HIGH);
      }
    break;
 
    case 1: // Amarelo carros
      if (currentMillis - lastChange >= yellowTime) {
        state = 2;
        lastChange = currentMillis;
 
        digitalWrite(carYellow, LOW);
        digitalWrite(carRed, HIGH);
 
        openPedestrian();
      }
    break;
 
    case 2:
      // Espera a função openPedestrian terminar
      state = 0;
      lastChange = millis();
      digitalWrite(carRed, LOW);
      digitalWrite(carGreen, HIGH);
    break;
  }
 
  if(state != 2){
    clearDisplay();
  }
}
 
void openPedestrian() {
 
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);
 
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
 
  digitalWrite(pedGreen, LOW);
  digitalWrite(pedRed, HIGH);
  noTone(buzzer);
  clearDisplay();
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