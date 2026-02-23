# 🚦 Semáforo Inclusivo para Pessoas Surdas e Cegas 🌸

## 💖 Uma Iniciativa Inclusiva

*Tecnologia com propósito, inclusão com estilo* ✨

---

## 📌 Sobre o Projeto

Este projeto foi desenvolvido por um grupo que uniu tecnologia e acessibilidade para criar um semáforo inclusivo utilizando Arduino, atendendo pessoas com deficiência visual e auditiva.

---

## 🎯 Funcionalidades

- **Sinalização Visual Tradicional**: LEDs para veículos e pedestres
- **Display de 7 Segmentos**: Contagem regressiva de 5 segundos
- **Sinal Sonoro Adaptativo**:
  - Primeiros 3 segundos: tom contínuo (2500 Hz)
  - Últimos 2 segundos: tom intermitente com display piscando
- **Botão de Solicitação**: Travessia a cada 5 segundos
- **Tempo de Travessia**: 5 segundos

---

## Tecnologias e Código Utilizado

🧠 Plataforma
Arduino Uno: Microcontrolador responsável pelo processamento e controle de todos os componentes

🔌 Linguagem de Programação
C/C++ (Arduino IDE): Código estruturado com funções específicas para controle de timing, lógica de estados e acionamento dos dispositivos

⚙️ Lógica do Sistema
Controle de Estados: Sequência definida para veículos (verde → amarelo → vermelho) e pedestres (vermelho → verde)

Interrupção por Botão: Leitura digital com debounce temporal via millis()

Contagem Regressiva: Implementada com loop for e matriz de segmentos para display

Sinal Sonoro: Utilização da função tone() para gerar frequência de 2500Hz, alternando entre modo contínuo e intermitente

Temporização: Gerenciada com delay() e millis() para precisão nos intervalos

📟 Display de 7 Segmentos
Matriz digits[10][7] mapeia quais segmentos acender para cada número (0 a 9)

Funções showDigit() e clearDisplay() controlam a exibição

🔊 Buzzer
Gerador de tons com padrões distintos para indicar diferentes fases da travessia

---
## 🔧 Componentes

- 1x Arduino Uno
- 3x LEDs (vermelho, amarelo, verde) para veículos
- 2x LEDs (vermelho, verde) para pedestres
- 1x Display 7 segmentos (cátodo comum)
- 1x Buzzer
- 1x Botão
- Resistores: 220Ω e 10kΩ
- Protoboard e jumpers

---

## 📋 Pinagem

| Componente | Pino |
|------------|------|
| LED Vermelho (Carros) | 12 |
| LED Amarelo (Carros) | 11 |
| LED Verde (Carros) | 10 |
| LED Vermelho (Pedestres) | 8 |
| LED Verde (Pedestres) | 9 |
| Buzzer | 7 |
| Botão | 2 |
| Segmento A | 3 |
| Segmento B | 4 |
| Segmento C | 5 |
| Segmento D | 6 |
| Segmento E | A0 |
| Segmento F | A1 |
| Segmento G | A2 |

---

## ⚙️ Funcionamento

1. **Estado Inicial**: Verde para carros, vermelho para pedestres
2. **Solicitação**: Botão pressionado → aguarda 5s → inicia sequência
3. **Transição**:
   - Verde dos carros pisca (3s)
   - Amarelo dos carros (3s)
   - Vermelho dos carros
4. **Travessia**:
   - Verde para pedestres (5s)
   - Display mostra contagem regressiva 5→1
   - Som contínuo (3s) → intermitente (2s)
5. **Retorno**: Verde para carros

---

## 🚀 Instalação

1. Monte o circuito conforme pinagem
2. Conecte o Arduino ao computador
3. Abra o código no Arduino IDE
4. Selecione a placa "Arduino Uno"
5. Carregue o código
6. Pressione o botão para testar

---

## 🔍 Observações

- Display de **cátodo comum** (segmentos acendem com HIGH)
- Tempo mínimo entre solicitações: 5 segundos
- Use resistores para proteção dos componentes

---

## 🌟 Diferenciais Inclusivos

- **Para pessoas cegas**: Sinais sonoros com padrões distintos
- **Para pessoas surdas**: Display visual com contagem regressiva
- **Design universal**: Estímulos visuais e sonoros combinados

---

## 👩‍💻 Sobre o Grupo

Projeto desenvolvido por um grupo apaixonado por tecnologia e inclusão. Acreditamos que a tecnologia pode transformar vidas e construir um mundo mais acessível para todos.

---

## 📝 Licença

Open-source para fins educacionais e inclusivos.

---

 💖♿