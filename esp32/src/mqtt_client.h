#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "components/Sonar.h"
#include "components/Led.h"

class MQTT_Client {
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
    MQTT_Client(const char* ssid, const char* password, const char* mqtt_server, const char* topic);
    void setup();
    void loop();

private:
    void setup_wifi();
    void callback(char* topic, byte* payload, unsigned int length);
    void reconnect();
    Sonar* sonar;
    Led* greenLed;
    Led * redLed;
};

#endif
