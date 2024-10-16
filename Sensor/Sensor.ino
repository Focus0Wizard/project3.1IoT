#include "UltrasonicSensor.h"
#include "SensorServer.h"

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;

const char *SSID = "H_V";
const char *PASSWORD = "alberto123";
const char *MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 1883;
const char *MQTT_TOPIC = "control/sensor";

UltrasonicSensor ultrasonicSensor(TRIG_PIN, echoPin);
SensorServer mqttServerInstance(SSID, PASSWORD, MQTT_SERVER, MQTT_PORT, MQTT_TOPIC);

void setup()
{
  Serial.begin(115200);

  ultrasonicSensor.initialize();

  mqttServerInstance.connectToWiFi();
  mqttServerInstance.setupMQTT();
}

void loop()
{
  mqttServerInstance.loop();

  float distance = ultrasonicSensor.readDistance();

  mqttServerInstance.sendDistance(distance);

  delay(1000);
}
