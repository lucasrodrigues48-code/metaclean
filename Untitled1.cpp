
#include <DHT.h>

// Sensor DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Sensor HC-SR04
#define TRIG 5
#define ECHO 18

// Sensor MQ-5
#define MQ5 34

// Limite de temperatura
#define LIMITE_TEMP 50

// Limite de distância
#define LIMITE_DIST 20

// Limite do gás (ajustável)
#define LIMITE_GAS 2000

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(MQ5, INPUT);

  Serial.println("SISTEMA DE MONITORAMENTO INICIADO");
}

void loop() {

  // Leitura da temperatura
  float temperatura = dht.readTemperature();

  // Leitura da distância
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 30000);
  float distancia = duracao * 0.0343 / 2;

  // Leitura do gás
  int gas = analogRead(MQ5);

  Serial.println("-------------------------");

  // Temperatura
  if (!isnan(temperatura)) {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" C");

    if (temperatura > LIMITE_TEMP) {
      Serial.println("ALERTA: TEMPERATURA ALTA!");
    }
  } else {
    Serial.println("Erro na leitura do DHT11");
  }

  // Distância
  if (duracao > 0) {
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    if (distancia > LIMITE_DIST) {
      Serial.println("ALERTA: DISTANCIA MAIOR QUE 20 CM!");
    }
  } else {
    Serial.println("Distancia fora do alcance");
  }

  // Gás
  Serial.print("Nivel de gas: ");
  Serial.println(gas);

  if (gas > LIMITE_GAS) {
    Serial.println("ALERTA: GAS DETECTADO!");
  }

  delay(2000);
}
