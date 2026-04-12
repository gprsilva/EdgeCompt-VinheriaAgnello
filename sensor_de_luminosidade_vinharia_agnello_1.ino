// Definição dos pinos
const int LDR = A0;
const int LED_VERDE = 13;
const int LED_AMARELO = 12;
const int LED_VERMELHO = 11;
const int BUZZER = 4;

int valorLDR = 0; // Variável para guardar a leitura da luz

void setup() {
  // Configuração dos pinos
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Inicia o monitor serial para você ver os números no Tinkercad
  Serial.begin(9600);
}

void loop() {
  // 1. Lê o valor analógico do LDR (0 a 1023)
  valorLDR = analogRead(LDR);
  
  // Mostra o valor no Monitor Serial
  Serial.print("Luminosidade: ");
  Serial.println(valorLDR);

  // 2. Lógica dos LEDs e Alarme
  if (valorLDR <= 100) {
    // Ambiente OK (Penumbra)
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(BUZZER, LOW);
  } 
  else if (valorLDR > 100 && valorLDR <= 900) {
    // Nível de Alerta
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(BUZZER, LOW);
  } 
  else {
    // Problema: Muita luz! 
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    
    // Tocar o buzzer por 3 segundos 
    tone(BUZZER, 650); // Função utilizada para colocar um som diferente no BUZZER
    delay(3000); 
    noTone(BUZZER);
    delay(1000); 
  }


}