#include "ServoActuator.h"
#include "ActuatorServer.h"

// Actualiza estos valores con los de tu red
const char* ssid = "H_V";
const char* password = "alberto123";
const char* mqtt_server = "broker.hivemq.com";

ServoActuator servoActuator(16, 90, 15);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");
  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  int receivedValue = message.toInt();
  if (receivedValue >= 0 && receivedValue <= 180) {
    servoActuator.setTargetAngle(receivedValue);
    Serial.print("Nuevo ángulo objetivo: ");
    Serial.println(receivedValue);
  } else {
    Serial.println("Valor fuera de rango (0-180)");
  }
}

ActuatorServer actuatorServer(ssid, password, mqtt_server, callback);

void setup() {
  Serial.begin(115200);
  servoActuator.initialize();
  actuatorServer.connectToWiFi();
  actuatorServer.setupMQTT();
}

void loop() {
  actuatorServer.loop();
  servoActuator.moveToTarget();
}
