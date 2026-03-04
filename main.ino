#include <Wire.h>
#include "RTClib.h"
 
RTC_DS1307 rtc;
 
// ===== PINOS =====
int carRed = 12;
int carYellow = 11;
int carGreen = 10;
 
int pedRed = 8;
int pedGreen = 9;
 
int buzzer = 7;
int button = 2;
 
// Display
int segA = 3;
int segB = 4;
int segC = 5;
int segD = 6;
int segE = A0;
int segF = A1;
int segG = A2;
 
// ===== TEMPOS =====
unsigned long greenTime;
unsigned long yellowTime;
unsigned long lastChange = 0;
 
int state = 0;
bool botaoPressionado = false;
bool pedHdePico = false;
 
// ===== DISPLAY =====
int digits[10][7] = {
{1,1,1,1,1,1,0},
{0,1,1,0,0,0,0},
{1,1,0,1,1,0,1},
{1,1,1,1,0,0,1},
{0,1,1,0,0,1,1},
{1,0,1,1,0,1,1},
{1,0,1,1,1,1,1},
{1,1,1,0,0,0,0},
{1,1,1,1,1,1,1},
{1,1,1,1,0,1,1}
};
 
// ===== SETUP =====
void setup() {
Serial.begin(9600);
 
if (!rtc.begin()) {
Serial.println("RTC NAO ENCONTRADO");
while (1);
}
 
//rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // usa só 1x!
 
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
 
digitalWrite(carGreen, HIGH);
digitalWrite(pedRed, HIGH);
 
lastChange = millis();
}
 
// ===== LOOP =====
void loop() {
 
DateTime now = rtc.now();
int hora = now.hour();
bool horaDePico = (hora >=17 && hora<19 || hora>=07 && hora<09);
 
if(horaDePico){
greenTime = 9000;
yellowTime = 3000;
pedHdePico = true;
}
else{
greenTime = 7000;
yellowTime = 2000;
pedHdePico = false;
}
 
bool modoNoturno = (hora >= 22 || hora < 6);
 
// ===== MODO NOTURNO =====
static unsigned long lastBlink = 0;
static bool ledState = false;
 
if (modoNoturno) {
 
digitalWrite(carGreen, LOW);
digitalWrite(carRed, LOW);
 
// piscar
if (millis() - lastBlink >= 500) {
lastBlink = millis();
ledState = !ledState;
digitalWrite(carYellow, ledState);
}
 
// botão
if (digitalRead(button) == HIGH) {
//conf que apertou
tone(buzzer, 1000);
delay(100);
noTone(buzzer);
 
digitalWrite(carYellow, LOW);
digitalWrite(carRed, HIGH);
botaoPressionado= true;
delay(2000);
openPedestrian();
botaoPressionado= false;
delay(2000);
digitalWrite(carRed, LOW);
}
 
return;
}
else{
 
 
// ===== MODO NORMAL =====
unsigned long currentMillis = millis();
 
if (digitalRead(button) == HIGH && state == 0) {
botaoPressionado = true;
//conf que apertou
tone(buzzer, 1000);
delay(100);
noTone(buzzer);
 
 
for(int i=0;i<3;i++){
digitalWrite(pedRed, LOW);
delay(100);
digitalWrite(pedRed, HIGH);
delay(100);
}
 
state = 1;
lastChange = currentMillis;
 
digitalWrite(carGreen, LOW);
digitalWrite(carYellow, HIGH);
}
 
switch(state) {
 
case 0:
if (currentMillis - lastChange >= greenTime) {
state = 1;
lastChange = currentMillis;
 
digitalWrite(carGreen, LOW);
digitalWrite(carYellow, HIGH);
}
break;
 
case 1:
if (currentMillis - lastChange >= yellowTime) {
state = 2;
lastChange = currentMillis;
 
digitalWrite(carYellow, LOW);
digitalWrite(carRed, HIGH);
 
openPedestrian();
}
break;
 
case 2:
state = 0;
lastChange = millis();
 
digitalWrite(carRed, LOW);
digitalWrite(carGreen, HIGH);
 
botaoPressionado = false;
break;
}
 
if(state != 2){
clearDisplay();
}
}
}
 
// ===== PEDESTRE =====
void openPedestrian() {
 
digitalWrite(pedRed, LOW);
digitalWrite(pedGreen, HIGH);
 
int tempo = botaoPressionado ? 8 : 5;
if (pedHdePico) tempo=7;
for (int i = tempo; i > 0; i--) {
 
showDigit(i);
 
if (i > 2) {
tone(buzzer, 2000);
delay(300);
noTone(buzzer);
delay(700);
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
 
if(i <= 2){
clearDisplay();
delay(100);
showDigit(i);
}
}
 
digitalWrite(pedGreen, LOW);
digitalWrite(pedRed, HIGH);
noTone(buzzer);
clearDisplay();
}
 
// ===== DISPLAY =====
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
 