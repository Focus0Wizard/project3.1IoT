#include "ServoActuator.h"
#include "ActuatorServer.h"

const int PIN = 16;
const int INITIAL_ANGLE = 90;
const int DELAY_TIME = 15;

const char *SSID = "H_V";
const char *PASSWORD = "alberto123";
const char *MQTT_SERVER = "broker.hivemq.com";

ServoActuator servoActuator(PIN, INITIAL_ANGLE, DELAY_TIME);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("] ");
  String message = "";

  for (int i = 0; i < length; i++)
    message += (char)payload[i];
  Serial.println(message);

  int receivedValue = message.toInt();
  if (receivedValue >= 0 && receivedValue <= 180)
  {
    servoActuator.setTargetAngle(receivedValue);
    Serial.print("New target angle: ");
    Serial.println(receivedValue);
  }
  else
    Serial.println("Value out of range (0-180)");
}

ActuatorServer actuatorServer(SSID, PASSWORD, MQTT_SERVER, callback);

void setup()
{
  Serial.begin(115200);
  servoActuator.initialize();
  actuatorServer.connectToWiFi();
  actuatorServer.setupMQTT();
}

void loop()
{
  actuatorServer.loop();
  servoActuator.moveToTarget();
}
