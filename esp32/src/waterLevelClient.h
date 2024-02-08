#ifndef WATER_LEVEL_CLIENT_H
#define WATER_LEVEL_CLIENT_H

#include "mqtt_client.h"
#include "config.h"
#include "components/Led.h"

class WaterLevelClient : public MQTT_Client {
public:
    WaterLevelClient(const char* ssid, const char* password, const char* mqtt_server, const char* topic)
        : MQTT_Client(ssid, password, mqtt_server, topic) {
            sonar = new Sonar(ECHO_PIN, TRIG_PIN, SONAR_TIME);
        }

    void handleData(byte* payload, unsigned int length) {
        // Non utilizzato per questo client
    }

    void readAndPublishDistance() {
        // Leggi la distanza dal sensore
        int distance = sonar->getDistance();
        Serial.println(String("Distance: ") + distance);

        // Crea un messaggio nel buffer
        snprintf(se, sizeof(msg), "%d", distance);

        Serial.println(String("Publishing message: ") + msg);

        // Pubblica il messaggio
        client.publish(topic, msg);
    }

private:
    Sonar* sonar;
    Led * led;
};

#endif
