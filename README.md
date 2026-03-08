# 🚦 Semáforo Inclusivo 🌸✨

## 💖 Uma Iniciativa Inclusiva

*Tecnologia com propósito, inclusão com estilo* 💙♿

Assista ao vídeo do YouTube:
https://youtu.be/LLgSQZXqBrA?si=M8V0kkRBXJ0o03g6 

Este projeto foi desenvolvido por um grupo que uniu tecnologia e acessibilidade para criar um semáforo inclusivo utilizando Arduino, atendendo pessoas com deficiência visual, auditiva e motora.

---

## 📌 Sobre o Projeto

O sistema simula um semáforo de pedestres com recursos adaptados:

- **Sinalização Visual Tradicional**: LEDs para veículos (verde, amarelo, vermelho) e pedestres (vermelho, verde)
- **Display de 7 Segmentos**: Contagem regressiva durante a travessia
- **Sinal Sonoro Adaptativo**: Tons diferentes para indicar o tempo restante
- **Botão de Solicitação de Travessia**: Permite ao pedestre chamar a abertura do semáforo
- **Modo Noturno Automático**: Entre 22h e 6h, o semáforo opera em pisca‑amarelo, reduzindo o consumo e mantendo a segurança
- **Controle por RTC**: Utiliza um módulo de relógio em tempo real para alternar os modos automaticamente

---

## 🎯 Funcionalidades Detalhadas

- **Ciclo dos Carros**: 10 segundos de verde → 2 segundos de amarelo → vermelho (enquanto pedestre atravessa)
- **Travessia do Pedestre**:
  - **Duração**: 5 segundos (ciclo automático) ou 8 segundos (quando solicitado pelo botão)
  - **Display**: Contagem regressiva de 5 a 1 (ou 8 a 1)
  - **Sinal Sonoro**:
    - Primeiros segundos (acima de 2): tom contínuo de 2000 Hz por 300 ms a cada segundo
    - Últimos 2 segundos: 4 toques rápidos (2500 Hz, 125 ms ligado / 125 ms desligado) – indicando urgência
    - Nos últimos 2 segundos, o LED verde do pedestre também pisca
- **Botão de Solicitação**:
  - Ao ser pressionado, o sistema pisca o LED vermelho do pedestre 3 vezes para confirmar o pedido
  - Se os carros ainda estiverem no verde, o amarelo é acionado imediatamente, agilizando a travessia
- **Modo Noturno (22h – 6h)**:
  - LEDs verde e vermelho dos carros apagados
  - LED amarelo piscando a cada 500 ms (usando `millis()` para não travar o sistema)
  - Botão ainda ativo: ao ser pressionado, abre o vermelho dos carros e libera a travessia normalmente, retornando depois ao pisca‑amarelo

---

## 🧰 Componentes Utilizados

| Quantidade | Componente                     |
|------------|--------------------------------|
| 1          | Arduino Uno                    |
| 1          | Módulo RTC DS1307              |
| 3          | LED vermelho (carros + pedestre)|
| 2          | LED amarelo (carros)           |
| 2          | LED verde (carros + pedestre)  |
| 1          | Display de 7 segmentos (cátodo comum) |
| 1          | Buzzer passivo                 |
| 1          | Botão (push button)            |
| 5          | Resistor 220Ω (para LEDs)      |
| 1          | Resistor 10kΩ (pull‑down do botão) |
| 1          | Protoboard                     |
| Vários     | Jumpers                         |

---

## 🔌 Pinagem (Conexões)

| Componente               | Pino no Arduino |
|--------------------------|-----------------|
| LED Vermelho (Carros)    | 12              |
| LED Amarelo (Carros)     | 11              |
| LED Verde (Carros)       | 10              |
| LED Vermelho (Pedestre)  | 8               |
| LED Verde (Pedestre)     | 9               |
| Buzzer                   | 7               |
| Botão                    | 2               |
| Display – Segmento A     | 3               |
| Display – Segmento B     | 4               |
| Display – Segmento C     | 5               |
| Display – Segmento D     | 6               |
| Display – Segmento E     | A0              |
| Display – Segmento F     | A1              |
| Display – Segmento G     | A2              |
| RTC – SDA                | A4 (I2C)        |
| RTC – SCL                | A5 (I2C)        |

*Obs.: O display é de **cátodo comum** – o pino comum deve ser ligado ao GND. Cada segmento deve ter um resistor de 220Ω em série.*

---

## ⚙️ Lógica do Sistema (Explicação Técnica)

### 🧠 Plataforma
- **Arduino Uno**: Microcontrolador responsável pelo processamento e controle de todos os componentes.

### 🔌 Linguagem de Programação
- **C/C++ (Arduino IDE)**: Código estruturado com funções específicas para controle de temporização, lógica de estados e acionamento dos dispositivos.

### ⚙️ Lógica do Funcionamento
- **Controle de Estados**: Sequência definida para veículos (verde → amarelo → vermelho) e pedestres (vermelho → verde). Os estados são gerenciados por uma máquina de estados simples com variável `state`.
- **Leitura do Botão com Debounce Implícito**: O botão é lido diretamente no `loop()`. Para evitar múltiplos acionamentos, uma confirmação visual (pisca do LED vermelho do pedestre) é usada.
- **Temporização**:
  - `millis()`: Controla o pisca‑amarelo noturno e as mudanças de estado no modo normal.
  - `delay()`: Utilizado apenas dentro da função `openPedestrian()` durante a contagem regressiva (não ideal, mas mantido para simplicidade no escopo do projeto).
- **RTC (DS1307)**: Fornece a hora atual para ativar o modo noturno automaticamente (22h – 6h).
- **Display de 7 Segmentos**:
  - Matriz `digits[10][7]` mapeia quais segmentos acender para cada número (0 a 9).
  - Funções `showDigit()` e `clearDisplay()` controlam a exibição.
- **Sinal Sonoro**:
  - `tone(buzzer, frequencia)`: Gera os tons.
  - Padrões distintos:
    - Tempo > 2s: tom contínuo de 2000 Hz por 300 ms a cada segundo.
    - Tempo ≤ 2s: 4 pulsos rápidos de 2500 Hz por segundo, com o LED verde do pedestre piscando junto.
- **Modo Noturno**: O amarelo pisca usando `millis()` (sem `delay`), permitindo que o botão continue sendo verificado a cada iteração do `loop()`.

---

## 🚀 Instalação e Uso

1. **Monte o circuito** conforme a tabela de pinagem.
2. **Instale as bibliotecas necessárias**:
   - `RTClib` (para o módulo RTC)
   - `Wire` (já inclusa na IDE Arduino)
3. **Ajuste a hora no RTC**:
   - No código, descomente a linha:
     ```cpp
     // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // usa só 1x!
     ```
   - Carregue o programa **uma única vez** para gravar a data/hora do computador no módulo.
   - Comente a linha novamente e recarregue o código para evitar que o RTC seja reajustado a cada reinicialização.
4. **Conecte o Arduino ao computador**, selecione a placa "Arduino Uno" e a porta correta.
5. **Carregue o código**.
6. **Teste**:
   - Pressione o botão para solicitar a travessia.
   - Observe a sequência de LEDs, a contagem no display e os sons do buzzer.
   - Para testar o modo noturno, ajuste manualmente a hora no RTC (alterando o código temporariamente) ou aguarde o horário programado.

---

## 🔍 Observações Importantes

- O display utilizado é de **cátodo comum**. Se for de ânodo comum, será necessário inverter a lógica dos segmentos (HIGH/LOW).
- O RTC necessita de uma bateria CR2032 para manter a hora quando o Arduino estiver desligado.
- Os resistores de 220Ω são essenciais para limitar a corrente nos LEDs e no display – não os omita.
- O botão deve ter um resistor pull‑down de 10kΩ para evitar flutuações.

---

## 🌟 Diferenciais Inclusivos

- **Para pessoas cegas**: Sinais sonoros com padrões distintos (contínuo x intermitente) permitem saber quanto tempo resta para atravessar com segurança.
- **Para pessoas surdas**: Display visual com contagem regressiva e LEDs indicam claramente o momento da travessia.
- **Design universal**: A combinação de estímulos visuais e sonoros garante que todos, independentemente de suas capacidades sensoriais, possam utilizar o semáforo com autonomia.

---

## 👩‍💻 Sobre o Grupo

Projeto desenvolvido por um grupo apaixonado por tecnologia e inclusão. Acreditamos que a tecnologia pode transformar vidas e construir um mundo mais acessível para todos.

---

## 📝 Licença

Open-source para fins educacionais e inclusivos. Sinta‑se à vontade para modificar, melhorar e compartilhar!

---

💖♿ **Tecnologia que abraça a diversidade** 🌈✨