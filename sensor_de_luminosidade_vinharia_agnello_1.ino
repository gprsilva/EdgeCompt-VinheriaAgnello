// Bibliotecas
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definição dos pinos
const int LDR = A0;
const int TMP = A1;
const int UMID = A2;
const int LED_VERMELHO = 11;
const int LED_AMARELO = 12;
const int LED_VERDE = 13;
const int BUZZER = 4;

// Definição dos limites
const int LIMITE_LUZ_ESCURO = 30;
const int LIMITE_LUZ_MEIA = 70;
const float TEMP_MIN = 10.0;
const float TEMP_MAX = 15.0;
const float UMID_MIN = 50.0;
const float UMID_MAX = 70.0;

// Definição do número de leituras para média
const int NUM_LEITURAS = 5;
const int INTERVALO_EXIBICAO = 5000;
const int INTERVALO_LEITURA = 1000;

// LCD I2C no endereço 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Arrays para armazenar as leituras
float leituras_temp[NUM_LEITURAS];
float leituras_umid[NUM_LEITURAS];
int leituras_luz[NUM_LEITURAS];
int indice = 0;

// Variáveis para as médias
float media_temp = 0.0;
float media_umid = 0.0;
int media_luz = 0;

// Variáveis para controle de tempo
unsigned long tempo_exibicao = 0;
unsigned long tempo_leitura = 0;

// Símbolos personalizados para o LCD (ponto extra!)
byte simbolo_vinho[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte simbolo_graus[8] = {
  0b01100,
  0b10010,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte simbolo_gota[8] = {
  0b00100,
  0b01110,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000
};

byte simbolo_sol[8] = {
  0b00000,
  0b10101,
  0b01110,
  0b11111,
  0b01110,
  0b10101,
  0b00000,
  0b00000
};

// ============================================================
// Função para configurar o sistema
// ============================================================
void setup() {
  // Configuração dos pinos
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Inicia o monitor serial
  Serial.begin(9600);
  Serial.println("Vinheria Agnello - Sistema Iniciado");
  
  // Desliga todos os LEDs
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);
  
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
  
  // Cria os símbolos personalizados (ponto extra!)
  lcd.createChar(0, simbolo_vinho);
  lcd.createChar(1, simbolo_graus);
  lcd.createChar(2, simbolo_gota);
  lcd.createChar(3, simbolo_sol);
  
  // Tela de boas-vindas
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.print(" Vinheria");
  lcd.setCursor(0, 1);
  lcd.write(0);
  lcd.print(" Agnello ");
  lcd.write(0);
  delay(3000);
  
  // Inicializa os arrays com zero
  for (int i = 0; i < NUM_LEITURAS; i++) {
    leituras_temp[i] = 0.0;
    leituras_umid[i] = 0.0;
    leituras_luz[i] = 0;
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Monitorando...");
}

// ============================================================
// Função principal que fica em loop
// ============================================================
void loop() {
  unsigned long agora = millis();
  
  // Faz a leitura dos sensores a cada 1 segundo
  if (agora - tempo_leitura >= INTERVALO_LEITURA) {
    tempo_leitura = agora;
    lerSensores();
  }
  
  // Calcula a média e exibe a cada 5 segundos
  if (agora - tempo_exibicao >= INTERVALO_EXIBICAO) {
    tempo_exibicao = agora;
    calcularMedias();
    exibirNoLCD();
    exibirNoSerial();
  }
  
  // Atualiza os alertas dos LEDs e Buzzer
  atualizarAlertas();
}

// ============================================================
// Função para ler todos os sensores
// ============================================================
void lerSensores() {
  int valorLuz, valorTMP, valorUmid;
  float tensao, temperatura;
  
  // Lê o LDR e mapeia para 0-100
  valorLuz = analogRead(LDR);
  leituras_luz[indice] = map(valorLuz, 0, 1023, 0, 100);
  
  // Lê o TMP36 e converte para temperatura em Celsius
  valorTMP = analogRead(TMP);
  tensao = valorTMP * (5.0 / 1023.0);
  temperatura = (tensao - 0.5) * 100.0;
  leituras_temp[indice] = temperatura;
  
  // Lê o potenciômetro e mapeia para 0-100 (umidade)
  valorUmid = analogRead(UMID);
  leituras_umid[indice] = map(valorUmid, 0, 1023, 0, 100);
  
  // Avança o índice
  indice = indice + 1;
  if (indice >= NUM_LEITURAS) {
    indice = 0;
  }
}

// ============================================================
// Função para calcular as médias
// ============================================================
void calcularMedias() {
  float somaTemp = 0.0;
  float somaUmid = 0.0;
  int somaLuz = 0;
  
  for (int i = 0; i < NUM_LEITURAS; i++) {
    somaTemp = somaTemp + leituras_temp[i];
    somaUmid = somaUmid + leituras_umid[i];
    somaLuz = somaLuz + leituras_luz[i];
  }
  
  media_temp = somaTemp / NUM_LEITURAS;
  media_umid = somaUmid / NUM_LEITURAS;
  media_luz = somaLuz / NUM_LEITURAS;
}

// ============================================================
// Função para exibir os valores no LCD
// ============================================================
void exibirNoLCD() {
  // Primeira tela: Temperatura e Umidade
  lcd.clear();
  
  // Linha 0: Temperatura
  lcd.setCursor(0, 0);
  if (media_temp >= TEMP_MIN && media_temp <= TEMP_MAX) {
    lcd.print("Temp OK  ");
  } else if (media_temp > TEMP_MAX) {
    lcd.print("Temp ALTA");
  } else {
    lcd.print("Temp BAIX");
  }
  
  lcd.setCursor(10, 0);
  lcd.print(media_temp, 1);
  lcd.write(1); // Símbolo de graus
  lcd.print("C");
  
  // Linha 1: Umidade
  lcd.setCursor(0, 1);
  lcd.write(2); // Símbolo de gota
  lcd.print(" ");
  
  if (media_umid >= UMID_MIN && media_umid <= UMID_MAX) {
    lcd.print("Umid OK ");
  } else if (media_umid > UMID_MAX) {
    lcd.print("Umid ALT");
  } else {
    lcd.print("Umid BAI");
  }
  
  lcd.setCursor(11, 1);
  lcd.print(media_umid, 0);
  lcd.print("%");
  
  // Mostra temperatura e umidade por 2.5 segundos
  delay(2500);
  
  // Segunda tela: Luminosidade
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(3); // Símbolo de sol
  lcd.print(" Luminosidade");
  
  lcd.setCursor(0, 1);
  if (media_luz <= LIMITE_LUZ_ESCURO) {
    lcd.print("Ambiente OK   ");
  } else if (media_luz <= LIMITE_LUZ_MEIA) {
    lcd.print("Meia luz      ");
  } else {
    lcd.print("Muito claro!  ");
  }
  
  // Mostra luminosidade por 2.5 segundos
  delay(2500);
}

// ============================================================
// Função para exibir os valores no Monitor Serial
// ============================================================
void exibirNoSerial() {
  Serial.println("");
  Serial.println("=== STATUS DO AMBIENTE ===");
  Serial.print("Luminosidade: ");
  Serial.print(media_luz);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(media_temp, 1);
  Serial.println(" C");
  Serial.print("Umidade: ");
  Serial.print(media_umid, 0);
  Serial.println(" %");
  Serial.println("==========================");
}

// ============================================================
// Função para atualizar os alertas (LEDs e Buzzer)
// ============================================================
void atualizarAlertas() {
  int temAlerta = 0;
  
  // Desliga todos os LEDs primeiro
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);
  
  // Verifica a luminosidade
  if (media_luz <= LIMITE_LUZ_ESCURO) {
    // Requisito 1: Ambiente escuro -> LED Verde
    digitalWrite(LED_VERDE, HIGH);
  } 
  else if (media_luz <= LIMITE_LUZ_MEIA) {
    // Requisito 2: Meia luz -> LED Amarelo
    digitalWrite(LED_AMARELO, HIGH);
  } 
  else {
    // Requisito 3 e 4: Muito claro -> LED Vermelho + Buzzer
    digitalWrite(LED_VERMELHO, HIGH);
    temAlerta = 1;
  }
  
  // Verifica a temperatura
  if (media_temp < TEMP_MIN || media_temp > TEMP_MAX) {
    // Requisito 8: Temperatura fora do ideal -> LED Amarelo + Buzzer
    digitalWrite(LED_AMARELO, HIGH);
    temAlerta = 1;
  }
  
  // Verifica a umidade
  if (media_umid < UMID_MIN || media_umid > UMID_MAX) {
    // Requisito 11: Umidade fora do ideal -> LED Vermelho + Buzzer
    digitalWrite(LED_VERMELHO, HIGH);
    temAlerta = 1;
  }
  
  // Liga ou desliga o Buzzer com tom agradável
  if (temAlerta == 1) {
    tone(BUZZER, 1000); // Tom de 1000Hz (som agradável)
  } else {
    noTone(BUZZER);     // Desliga o buzzer
  }
}
