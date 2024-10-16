#ifndef ACTUATOR_SERVER_H
#define ACTUATOR_SERVER_H

#include <WiFi.h>
#include <PubSubClient.h>

class ActuatorServer {
  private:
    const char* ssid;
    const char* password;
    const char* mqtt_server;
    WiFiClient espClient;
    PubSubClient client;
    void (*callbackFunction)(char*, byte*, unsigned int);

  public:
    ActuatorServer(const char* ssid, const char* password, const char* mqtt_server, void (*callback)(char*, byte*, unsigned int)) 
      : ssid(ssid), password(password), mqtt_server(mqtt_server), client(espClient) {
      callbackFunction = callback;
    }

    void connectToWiFi() {
      delay(10);
      Serial.println();
      Serial.print("Conectando a ");
      Serial.println(ssid);

      WiFi.begin(ssid, password);

      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

      Serial.println();
      Serial.println("WiFi conectado");
      Serial.println("Dirección IP: ");
      Serial.println(WiFi.localIP());
    }

    void setupMQTT() {
      client.setServer(mqtt_server, 1883);
      client.setCallback(callbackFunction);
    }

    void reconnect() {
      while (!client.connected()) {
        Serial.print("Intentando conexión MQTT...");
        if (client.connect("fb1fdd90d95946ffbb7303c54658c936")) {
          Serial.println("conectado");
          client.subscribe("control/servo");
        } else {
          Serial.print("falló, rc=");
          Serial.print(client.state());
          Serial.println(" intentarlo de nuevo en 5 segundos");
          delay(5000);
        }
      }
    }

    void loop() {
      if (!client.connected()) {
        reconnect();
      }
      client.loop();
    }
};

#endif
