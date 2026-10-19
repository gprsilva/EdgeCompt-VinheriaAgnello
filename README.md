# 🍷 Sistema de Monitoramento Ambiental IoT - Vinheria Agnello
 
## 📋 Descrição do Projeto
 
Este projeto foi desenvolvido como evolução dos **Checkpoints 01, 02 e 05** da disciplina de **Edge Computing & Computer Systems** da **FIAP**.
 
A solução foi criada para atender às necessidades da **Vinheria Agnello**, permitindo monitorar continuamente as condições ambientais da adega, garantindo a qualidade dos vinhos armazenados.
 
Além do monitoramento local através de LEDs, buzzer e display LCD, a nova versão incorpora conceitos de **Internet das Coisas (IoT)** utilizando **ESP32**, **MQTT** e **FIWARE**, permitindo monitoramento remoto, histórico de dados e gerenciamento inteligente do ambiente.
 
---
 
# 🎯 Objetivo
 
Monitorar continuamente os principais fatores que influenciam a conservação dos vinhos:
 
- 🌡️ Temperatura
- 💧 Umidade
- ☀️ Luminosidade
 
A solução gera alertas locais e transmite os dados para uma plataforma IoT através do protocolo MQTT.
 
---
 
# 🌡️ Fatores Monitorados
 
| Fator | Condição Ideal | Risco |
|---------|---------|---------|
| Luminosidade | Até 30% | Raios UV alteram a composição química do vinho |
| Temperatura | 10°C a 15°C | Variações afetam aroma, sabor e envelhecimento |
| Umidade | 50% a 70% | Pode causar ressecamento das rolhas ou proliferação de fungos |
 
---
 
# 🚀 Funcionalidades Implementadas
 
## ✅ Monitoramento Ambiental
 
### ☀️ Luminosidade
 
- LED Verde → Ambiente Ideal
- LED Amarelo → Ambiente em Alerta
- LED Vermelho → Ambiente Crítico
- Acionamento do buzzer em situação crítica
 
### 🌡️ Temperatura
 
- Monitoramento contínuo
- Comparação com faixa ideal
- Geração de alertas automáticos
 
### 💧 Umidade
 
- Monitoramento contínuo
- Comparação com faixa ideal
- Geração de alertas automáticos
 
---
 
## ✅ Recursos Avançados
 
- Média móvel de 5 leituras
- Comunicação Wi-Fi
- Comunicação MQTT
- Envio de dados em JSON
- Status Inteligente da Adega
- Integração IoT
- Monitoramento remoto
- Histórico de dados
- Dashboard IoT
 
---
 
# ☁️ Evolução para IoT (Checkpoint 05)
 
A versão anterior realizava apenas monitoramento local.
 
Nesta etapa o sistema foi expandido para utilização de conceitos de Internet das Coisas através de:
 
- ESP32
- Wi-Fi
- MQTT
- FIWARE
- NGSIv2
- MyMQTT
 
---
 
# 🏗️ Arquitetura da Solução
 
```text
                 ┌────────────────┐
                 │     Sensores   │
                 │                │
                 │ LDR            │
                 │ TMP36          │
                 │ Umidade        │
                 └───────┬────────┘
                         │
                         ▼
                 ┌────────────────┐
                 │     ESP32      │
                 │                │
                 │ Processamento  │
                 │ Média Móvel    │
                 │ LEDs           │
                 │ Buzzer         │
                 └───────┬────────┘
                         │ Wi-Fi
                         ▼
                 ┌────────────────┐
                 │ MQTT Broker    │
                 └───────┬────────┘
                         │
                         ▼
                 ┌────────────────┐
                 │ FIWARE Orion   │
                 └───────┬────────┘
                         │
                         ▼
                 ┌────────────────┐
                 │ Histórico      │
                 │ Dashboard      │
                 └────────────────┘
