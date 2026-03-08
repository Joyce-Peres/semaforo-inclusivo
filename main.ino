#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

// ===== PINOS =====

int carroVermelho = 12;
int carroAmarelo = 11;
int carroVerde = 10;

int pedestreVermelho = 8;
int pedestreVerde = 9;

int buzzer = 7;
int botao = 2;

// Display

int segA = 3;
int segB = 4;
int segC = 5;
int segD = 6;
int segE = A0;
int segF = A1;
int segG = A2;

// ===== TEMPOS =====

unsigned long tempoVerde;
unsigned long tempoAmarelo;
unsigned long ultimoTempoTroca = 0;

int estado = 0;

bool botaoPressionado = false;
bool pedHdePico = false;

// ===== DISPLAY =====

int numerosDisplay[10][7] = {

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

pinMode(carroVermelho, OUTPUT);
pinMode(carroAmarelo, OUTPUT);
pinMode(carroVerde, OUTPUT);

pinMode(pedestreVermelho, OUTPUT);
pinMode(pedestreVerde, OUTPUT);

pinMode(buzzer, OUTPUT);
pinMode(botao, INPUT);

pinMode(segA, OUTPUT);
pinMode(segB, OUTPUT);
pinMode(segC, OUTPUT);
pinMode(segD, OUTPUT);
pinMode(segE, OUTPUT);
pinMode(segF, OUTPUT);
pinMode(segG, OUTPUT);

digitalWrite(carroVerde, HIGH);
digitalWrite(pedestreVermelho, HIGH);

ultimoTempoTroca = millis();

}

// ===== LOOP =====

void loop() {

DateTime agora = rtc.now();
int hora = agora.hour();

bool horaDePico = (hora >=17 && hora<19 || hora>=7 && hora<9);

if(horaDePico){

tempoVerde = 9000;
tempoAmarelo = 3000;
pedHdePico = true;

}

else{

tempoVerde = 7000;
tempoAmarelo = 2000;
pedHdePico = false;

}

bool modoNoturno = (hora >= 22 || hora < 6);

// ===== MODO NOTURNO =====

static unsigned long ultimoPiscar = 0;
static bool estadoLed = false;

if (modoNoturno) {

digitalWrite(carroVerde, LOW);
digitalWrite(carroVermelho, LOW);

 // piscar 

 if (millis() - ultimoPiscar >= 500) {

 ultimoPiscar = millis();
 estadoLed = !estadoLed;

 digitalWrite(carroAmarelo, estadoLed);

 }

 // botão 

 if (digitalRead(botao) == HIGH) {

//conf que apertou

tone(buzzer, 1000);
delay(100);
noTone(buzzer);

digitalWrite(carroAmarelo, LOW);
digitalWrite(carroVermelho, HIGH);

botaoPressionado = true;

delay(2000);

openPedestrian();

botaoPressionado = false;

delay(2000);

digitalWrite(carroVermelho, LOW);

 }

 return;

}

else{

// ===== MODO NORMAL =====

unsigned long tempoAtual = millis();

if (digitalRead(botao) == HIGH && estado == 0) {

 botaoPressionado = true;

 //conf que apertou

 tone(buzzer, 1000);
 delay(100);
 noTone(buzzer);

 for(int i=0;i<3;i++){

digitalWrite(pedestreVermelho, LOW);
delay(100);

digitalWrite(pedestreVermelho, HIGH);
delay(100);

 }

 estado = 1;

 ultimoTempoTroca = tempoAtual;

digitalWrite(carroVerde, LOW);
digitalWrite(carroAmarelo, HIGH);

}

switch(estado) {

case 0:

 if (tempoAtual - ultimoTempoTroca >= tempoVerde) {

 estado = 1;

 ultimoTempoTroca = tempoAtual;

digitalWrite(carroVerde, LOW);
digitalWrite(carroAmarelo, HIGH);

 }

break;

case 1:

 if (tempoAtual - ultimoTempoTroca >= tempoAmarelo) {

 estado = 2;

 ultimoTempoTroca = tempoAtual;

digitalWrite(carroAmarelo, LOW);
digitalWrite(carroVermelho, HIGH);

openPedestrian();

 }

break;

case 2:

 estado = 0;

 ultimoTempoTroca = millis();

digitalWrite(carroVermelho, LOW);
digitalWrite(carroVerde, HIGH);

 botaoPressionado = false;

break;

}

if(estado != 2){

clearDisplay();

}

}

}

// ===== PEDESTRE =====

void openPedestrian() {

digitalWrite(pedestreVermelho, LOW);
digitalWrite(pedestreVerde, HIGH);

int tempoTravessia;

if(botaoPressionado) tempoTravessia = 8;
else if (pedHdePico) tempoTravessia = 7;
else tempoTravessia = 5;

for (int i = tempoTravessia; i > 0; i--) {

showDigit(i);

 if (i > 2) {

tone(buzzer, 2000);
delay(300);

noTone(buzzer);
delay(700);

 } else {

 for (int j = 0; j < 4; j++) {

tone(buzzer, 2500);

digitalWrite(pedestreVerde, HIGH);
delay(125);

noTone(buzzer);

digitalWrite(pedestreVerde, LOW);
delay(125);

 }

 }

 if(i <= 2){

clearDisplay();
delay(100);

showDigit(i);

 }

}

digitalWrite(pedestreVerde, LOW);
digitalWrite(pedestreVermelho, HIGH);

noTone(buzzer);

clearDisplay();

}

// ===== DISPLAY =====

void showDigit(int num) {

digitalWrite(segA, numerosDisplay[num][0]);
digitalWrite(segB, numerosDisplay[num][1]);
digitalWrite(segC, numerosDisplay[num][2]);
digitalWrite(segD, numerosDisplay[num][3]);
digitalWrite(segE, numerosDisplay[num][4]);
digitalWrite(segF, numerosDisplay[num][5]);
digitalWrite(segG, numerosDisplay[num][6]);

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