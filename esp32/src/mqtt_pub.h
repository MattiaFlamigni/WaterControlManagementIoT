#ifndef MQTT_PUB_H
#define MQTT_PUB_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTT_Pub {
private:
    WiFiClient espClient;
    PubSubClient client;
    const char* ssid;
    const char* password;
    const char* mqtt_server;
    const char* topic;
    unsigned long lastMsgTime = 0;
    char msg[50];
    int value = 0;

public:
    MQTT_Pub(const char* ssid, const char* password, const char* mqtt_server, const char* topic);
    void setup();
    void loop();

private:
    void setup_wifi();
    void callback(char* topic, byte* payload, unsigned int length);
    void reconnect();
};

#endif
