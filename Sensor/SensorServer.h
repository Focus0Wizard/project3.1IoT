#ifndef SENSOR_SERVER_H
#define SENSOR_SERVER_H

#include <WiFi.h>
#include <PubSubClient.h>

class SensorServer
{
private:
  const char *ssid;
  const char *password;
  const char *mqttServer;
  int mqttPort;
  const char *mqttTopic;
  WiFiClient espClient;
  PubSubClient client;

public:
  SensorServer(const char *ssid, const char *password, const char *mqttServer, int mqttPort, const char *mqttTopic)
      : ssid(ssid), password(password), mqttServer(mqttServer), mqttPort(mqttPort), mqttTopic(mqttTopic), client(espClient) {}

  void connectToWiFi()
  {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
  }

  void setupMQTT()
  {
    client.setServer(mqttServer, mqttPort);
  }

  void reconnect()
  {
    while (!client.connected())
    {
      Serial.print("Connecting to the MQTT broker...");
      if (client.connect("ESP32Client"))
        Serial.println("Connected to MQTT broker");
      else
      {
        Serial.print("Fallo de conexión, rc=");
        Serial.print(client.state());
        Serial.println("Trying again in 5 seconds");
        delay(5000);
      }
    }
  }

  void sendDistance(float distance)
  {
    if (distance != -1)
    {
      char msg[50];
      dtostrf(distance, 6, 2, msg);
      Serial.print("Sending distance to MQTT server: ");
      Serial.println(msg);
      client.publish(mqttTopic, msg);
    }
  }

  void loop()
  {
    if (!client.connected())
      reconnect();
    
    client.loop();
  }
};

#endif
