# Monitoramento de Luminosidade - Vinheria Agnello 🍷

## Descrição do Projeto
Este projeto foi desenvolvido como parte do **Checkpoint 01** da disciplina de **Edge Computing & Computer Systems**. O objetivo é criar um sistema de monitoramento para a **Vinheria Agnello**, uma loja tradicional que está a expandir para o e-commerce e necessita de garantir a qualidade dos seus vinhos através do controlo ambiental.

A luminosidade é um fator crítico, especialmente para vinhos brancos e espumantes, pois os raios ultravioletas podem causar alterações nos compostos orgânicos e iniciar reações químicas indesejadas. Este sistema utiliza um Arduino para capturar a luminosidade e alertar o utilizador caso os níveis saiam da penumbra ideal.

## Componentes Utilizados
* **Arduino Uno**: Microcontrolador principal.
* **LDR (Light Dependent Resistor)**: Sensor para capturar a luminosidade do ambiente.
* **LEDs (Verde, Amarelo, Vermelho)**: Sinalização visual dos estados de luminosidade.
* **Buzzer**: Alarme sonoro para situações críticas.
* **Resistores**: 
    * 10kΩ para o divisor de tensão do LDR.
    * 330Ω para proteção dos LEDs.

## Pinagem do Hardware
Conforme a implementação realizada:
* **A0**: Entrada analógica para o sensor LDR.
* **Pino 13**: LED Verde (Ambiente OK).
* **Pino 12**: LED Amarelo (Nível de Alerta).
* **Pino 11**: LED Vermelho (Problema Crítico).
* **Pino 4**: Buzzer (Alarme Sonoro).

## Lógica de Funcionamento
O sistema monitoriza os valores analógicos (0 a 1023) e atua da seguinte forma:

1.  **Ambiente OK (0 a 100)**: Indica que a iluminação está suave (penumbra), ideal para o armazenamento. Apenas o **LED Verde** acende.
2.  **Nível de Alerta (101 a 900)**: Indica que a luminosidade começou a subir. Apenas o **LED Amarelo** acende.
3.  **Problema (> 900)**: Indica excesso de luz no ambiente. O **LED Vermelho** acende e o **Buzzer** soa por **3 segundos**. Se a luz persistir, o alarme volta a tocar.

## Como Reproduzir
1.  Monte o circuito no [Tinkercad](https://www.tinkercad.com/) seguindo a pinagem acima.
2.  Certifique-se de que os resistores estão configurados corretamente para evitar danos ao Arduino.
3.  Carregue o código fornecido (com a função `tone()` para o som do buzzer).
4.  Abra o **Monitor Serial** para acompanhar as leituras em tempo real.

## Desenvolvedores (Turma 1ESPQ)
* Guilherme Pereira Ruiz da Silva RM:573360
* Gustavo Bidin Marto RM:570272
* Gustavo Leal RM:569361
* Matheus Mandu de Lima RM:571348

