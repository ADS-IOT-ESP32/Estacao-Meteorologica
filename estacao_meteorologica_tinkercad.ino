// Simulação da Estação Meteorológica no Tinkercad (Arduino Uno)
// Cada potenciômetro representa um sensor; a chave representa o sensor de chuva.

const int PIN_UMIDADE = A0;   // potenciômetro 1 -> umidade
const int PIN_TEMP    = A1;   // potenciômetro 2 -> temperatura
const int PIN_PRESSAO = A2;   // potenciômetro 3 -> pressão absoluta
const int PIN_AR      = A3;   // potenciômetro 4 -> qualidade do ar
const int PIN_CHUVA   = 2;    // chave deslizante -> detector de chuva

const float ALTITUDE = 920.0; // altitude em metros

float umidade, temperatura, pressaoAbs, pressaoRel, ppm;
int leituraChuva;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_CHUVA, INPUT); // botão com resistor pull-down externo
}

void loop() {
  // Umidade: 0 a 100 %
  umidade = map(analogRead(PIN_UMIDADE), 0, 1023, 0, 100);

  // Temperatura: 0 a 50 ºC
  temperatura = analogRead(PIN_TEMP) * (50.0 / 1023.0);

  // Pressão absoluta: 300 a 1100 hPa
  pressaoAbs = 300.0 + analogRead(PIN_PRESSAO) * (800.0 / 1023.0);

  // Pressão relativa (nível do mar) - mesma ideia da função sealevel() do BMP180
  pressaoRel = pressaoAbs / pow(1.0 - (ALTITUDE / 44330.0), 5.255);

  // Qualidade do ar: 0 a 1000 ppm
  ppm = analogRead(PIN_AR) * (1000.0 / 1023.0);

  // Detector de chuva (mesma lógica do sensor real: 1 = seco, 0 = chuva)
  // Botão pressionado = HIGH, então invertemos: pressionado = 0 = chovendo
  leituraChuva = !digitalRead(PIN_CHUVA);

  Serial.println("===== Estacao Meteorologica IoT (simulada) =====");
  Serial.print("Umidade: ");          Serial.print(umidade, 0);     Serial.println(" %");
  Serial.print("Temperatura: ");      Serial.print(temperatura, 1); Serial.println(" C");
  Serial.print("Pressao absoluta: "); Serial.print(pressaoAbs, 1);  Serial.println(" hPa");
  Serial.print("Pressao relativa: "); Serial.print(pressaoRel, 1);  Serial.println(" hPa");
  Serial.print("Qualidade do ar: ");  Serial.print(ppm, 0);         Serial.println(" ppm");
  Serial.print("Detector de chuva: ");
  Serial.println(leituraChuva ? "Nao esta chovendo" : "Esta chovendo");
  Serial.println();

  delay(2000);
}
