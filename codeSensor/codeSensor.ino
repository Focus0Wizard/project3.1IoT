#include "UltrasonicSensor.h"
#include "SensorServer.h"

// Pines del sensor ultrasónico
const int trigPin = 5; 
const int echoPin = 18;

// Credenciales WiFi y configuración MQTT
const char* ssid = "H_V";
const char* password = "alberto123";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "control/sensor";

// Crear instancias de las clases
UltrasonicSensor ultrasonicSensor(trigPin, echoPin);
SensorServer mqttServerInstance(ssid, password, mqttServer, mqttPort, mqttTopic);

void setup() {
  Serial.begin(115200);

  // Inicializar sensor ultrasónico
  ultrasonicSensor.initialize();

  // Conectar a WiFi y configurar MQTT
  mqttServerInstance.connectToWiFi();
  mqttServerInstance.setupMQTT();
}

void loop() {
  // Mantener la conexión con el servidor MQTT
  mqttServerInstance.loop();

  // Leer distancia del sensor ultrasónico
  float distance = ultrasonicSensor.readDistance();

  // Enviar la distancia al servidor MQTT
  mqttServerInstance.sendDistance(distance);

  // Esperar antes de la próxima lectura
  delay(1000);
}
