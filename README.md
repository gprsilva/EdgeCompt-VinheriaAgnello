# 🍷 Sistema de Monitoramento Ambiental - Vinheria Agnello

## 📋 Descrição do Projeto

Este projeto foi desenvolvido como parte do **Checkpoint 01** e **Checkpoint 02** da disciplina de **Edge Computing & Computer Systems** da **FIAP**.

O sistema foi criado para atender às necessidades da **Vinheria Agnello**, uma vinheria tradicional que está expandindo seus negócios para o e-commerce e precisa garantir a qualidade dos seus vinhos através do monitoramento ambiental da adega.

---

# 🌡️ Fatores Monitorados

O armazenamento correto do vinho depende de três fatores críticos:

| Fator | Condição Ideal | Risco |
|---|---|---|
| **Luminosidade** | Penumbra (até 30%) | Raios UV alteram compostos orgânicos e causam reações químicas indesejadas |
| **Temperatura** | 10°C a 15°C | Flutuações térmicas acima de 3°C geram aromas indesejados e reduzem a vida do vinho |
| **Umidade** | 50% a 70% | Umidade baixa resseca as rolhas (oxidação) e umidade alta prolifera fungos e danifica rótulos |

---

# 🎯 Funcionalidades Implementadas

## ✅ Requisitos do Checkpoint 02

### 💡 Monitoramento de Luminosidade
- LED Verde: Ambiente em penumbra (ideal)
- LED Amarelo: Ambiente a meia luz (alerta)
- LED Vermelho + Buzzer: Ambiente muito claro (crítico)
- Mensagens no LCD:
  - `"Ambiente a meia luz"`
  - `"Ambiente muito claro"`

### 🌡️ Monitoramento de Temperatura (Sensor TMP36)
- Display LCD com temperatura atual em tempo real
- Indicação:
  - `"Temp OK"` (10°C a 15°C)
  - `"Temp ALTA"`
  - `"Temp BAIXA"`
- LED Amarelo + Buzzer fora da faixa ideal

### 💧 Monitoramento de Umidade (Potenciômetro Simulador)
- Display LCD com umidade atual em tempo real
- Indicação:
  - `"Umid OK"` (50% a 70%)
  - `"Umid ALTA"`
  - `"Umid BAIXA"`
- LED Vermelho + Buzzer fora da faixa ideal

### 🚀 Recursos Avançados
- Média móvel de 5 leituras
- Atualização do display a cada 5 segundos
- Display LCD 16x2 com interface I2C
- Buzzer com tom de 1000Hz
- Símbolos personalizados no LCD

---

# 🛠️ Componentes Utilizados

| Componente | Quantidade | Especificação |
|---|---|---|
| Arduino Uno | 1 | Microcontrolador principal |
| LCD 16x2 I2C | 1 | Display para visualização (0x27) |
| Sensor TMP36 | 1 | Sensor de temperatura |
| LDR | 1 | Sensor de luminosidade |
| Potenciômetro | 1 | Simulador de sensor de umidade |
| LED Verde | 1 | Indicação OK |
| LED Amarelo | 1 | Indicação de alerta |
| LED Vermelho | 1 | Indicação crítica |
| Buzzer | 1 | Alarme sonoro |
| Resistores 330Ω | 3 | Proteção dos LEDs |
| Resistor 10kΩ | 1 | Divisor de tensão do LDR |

---

# 🔌 Pinagem do Hardware

## 📥 Sensores

| Sensor | Pino Arduino | Descrição |
|---|---|---|
| LDR | A0 | Luminosidade |
| TMP36 | A1 | Temperatura |
| Potenciômetro | A2 | Umidade simulada |

## 📤 Saídas

| Componente | Pino Arduino | Função |
|---|---|---|
| LED Verde | 13 | Ambiente ideal |
| LED Amarelo | 12 | Alerta |
| LED Vermelho | 11 | Crítico |
| Buzzer | 4 | Alarme sonoro |

## 📺 LCD I2C

| LCD | Arduino |
|---|---|
| SDA | A4 |
| SCL | A5 |
| VCC | 5V |
| GND | GND |

---

# 📊 Lógica de Funcionamento

## 💡 Luminosidade

```text
0% - 30%   → LED Verde (Penumbra OK)
31% - 70%  → LED Amarelo (Meia Luz)
71% - 100% → LED Vermelho + Buzzer
```

## 🌡️ Temperatura

```text
< 10°C      → LED Amarelo + Buzzer
10°C - 15°C → LED Verde
> 15°C      → LED Amarelo + Buzzer
```

## 💧 Umidade

```text
< 50%      → LED Vermelho + Buzzer
50% - 70%  → LED Verde
> 70%      → LED Vermelho + Buzzer
```

---

# 📺 Display LCD

## Tela 1 — Temperatura e Umidade

```text
Temp OK 22.5°C
💧 Umid OK 65%
```

## Tela 2 — Luminosidade

```text
☀ Luminosidade
Ambiente OK
```

---

# 🎨 Símbolos Personalizados

O projeto utiliza símbolos customizados com `createChar()`.

| Índice | Símbolo | Descrição |
|---|---|---|
| 0 | 🍷 | Taça de vinho |
| 1 | ° | Graus Celsius |
| 2 | 💧 | Umidade |
| 3 | ☀ | Luminosidade |

## Código dos Símbolos

```cpp
byte simbolo_vinho[8] = {
  0b00000, 0b00100, 0b01110, 0b11111,
  0b11111, 0b01110, 0b00100, 0b00000
};

byte simbolo_graus[8] = {
  0b01100, 0b10010, 0b10010, 0b01100,
  0b00000, 0b00000, 0b00000, 0b00000
};

byte simbolo_gota[8] = {
  0b00100, 0b01110, 0b01110, 0b11111,
  0b11111, 0b11111, 0b01110, 0b00000
};

byte simbolo_sol[8] = {
  0b00000, 0b10101, 0b01110, 0b11111,
  0b01110, 0b10101, 0b00000, 0b00000
};
```

---

# 📁 Estrutura do Projeto

```bash
📦 Vinheria-Agnello-CP02
 ┣ 📜 vinheria_cp02.ino
 ┣ 📷 circuito.png
 ┣ 📄 README.md
 ┗ 🎥 video_explicativo.mp4
```

---

# 🚀 Como Executar

## 1️⃣ Simulação no Tinkercad

1. Acesse o Tinkercad
2. Monte o circuito
3. Carregue o código `.ino`
4. Clique em **Iniciar Simulação**
5. Ajuste os sensores
6. Observe LCD, LEDs e buzzer

---

## 2️⃣ Protótipo Físico

1. Monte o circuito
2. Conecte o Arduino via USB
3. Abra na Arduino IDE
4. Instale a biblioteca:

```text
LiquidCrystal_I2C
```

5. Faça upload para a placa

---

# 📈 Exemplo de Saída Serial

```text
=== STATUS DO AMBIENTE ===
Luminosidade: 25%
Temperatura: 12.3 C
Umidade: 65 %
==========================

Leitura #1 | Luz: 25% | Temp: 12.3C | Umid: 65%
Leitura #2 | Luz: 26% | Temp: 12.4C | Umid: 64%
Leitura #3 | Luz: 24% | Temp: 12.3C | Umid: 66%
Leitura #4 | Luz: 25% | Temp: 12.5C | Umid: 65%
Leitura #5 | Luz: 26% | Temp: 12.3C | Umid: 65%
```

---

# 🔧 Bibliotecas Utilizadas

| Biblioteca | Função |
|---|---|
| `Wire.h` | Comunicação I2C |
| `LiquidCrystal_I2C.h` | Controle do LCD |

---

# ⚠️ Observações

- O sensor de umidade é simulado com potenciômetro
- O Tinkercad não possui DHT11/DHT22
- O buzzer utiliza `tone()` em 1000Hz
- A média móvel reduz oscilações
- O LCD utiliza endereço I2C `0x27`

---

# 👨‍💻 Desenvolvedores

## 🎓 Turma 1ESPQ - FIAP

| Nome | RM |
|---|---|
| Guilherme Pereira Ruiz da Silva | 573360 |
| Gustavo Bidin Marto | 570272 |
| Gustavo Leal | 569361 |
| Matheus Mandu de Lima | 571348 |

---

# 📚 Disciplina

**Edge Computing & Computer Systems**  
Professor: **Lucas D. Augusto**

---

<p align="center">
Desenvolvido com ❤️ pela equipe Vinheria Agnello
</p>
